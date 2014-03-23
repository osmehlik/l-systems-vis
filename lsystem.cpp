
#include "lsystem.h"
#include <iostream>
#include <sstream>
#include <QMessageBox>


//LSystem::LSystem() {}
LSystem::LSystem(QObject *parent) : QObject(parent)
{
    setDefaultState();
}

LSystem::~LSystem()
{}

void LSystem::setDefaultState()
{
    start = "";
    rules.clear();
    interpretations.clear();
    startX = 0.5;
    startY = 0.5;
    startRot = 0;
    iterations = 8;
    backgroundColor = "#ffffff";
    foregroundColor = "#000000";
    stepLength = 10;
}

std::string LSystem::evolve(int iterations)
{
    std::string str(start);

    for (int i(0); i < iterations; ++i) {
        std::string strNextIter;

        // for each char
        for (size_t j(0); j < str.length(); ++j) {
            std::string currentCharAsString = str.substr(j,1);

            bool foundReplacement = false;

            for (Rules::iterator it(rules.begin()); it != rules.end(); ++it) {
                if (currentCharAsString == it->first) {
                    strNextIter += it->second;
                    foundReplacement = true;
                    break;
                }
            }

            if (!foundReplacement) {
                strNextIter += currentCharAsString;
            }
        }

        str = strNextIter;
    }

    return str;
}

void LSystem::save(QFile *f)
{
    if (!f->open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "Read only", "File rights disallow writting to file.");
        return;
    }

    QXmlStreamWriter writer;

    writer.setDevice(f);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("lsystem");

    writeStart(writer);
    writeRules(writer);
    writeSymbols(writer);
    writeParams(writer);

    writer.writeEndElement(); // lsystem
    writer.writeEndDocument();
}

void LSystem::writeStart(QXmlStreamWriter &writer)
{
    writer.writeStartElement("start");
    writer.writeCharacters(start.c_str());
    writer.writeEndElement(); // start
}

void LSystem::writeRules(QXmlStreamWriter &writer)
{
    typedef Rules::iterator RulesIt;

    writer.writeStartElement("rules");
    for (RulesIt it(rules.begin()); it != rules.end(); ++it) {
        writer.writeStartElement("rule");
        writer.writeAttribute("from", it->first.c_str());
        writer.writeAttribute("to", it->second.c_str());
        writer.writeEndElement(); // rule
    }
    writer.writeEndElement(); // rules
}


void LSystem::writeSymbols(QXmlStreamWriter &writer)
{
    writer.writeStartElement("symbols");
    for (size_t i(0); i < getNumInterpretations(); ++i) {
        const CharInterpretation &interpretation = getInterpretation(i);

        writer.writeStartElement("symbol");

        std::stringstream ss;

        ss << interpretation.symbol;

        writer.writeAttribute("name", ss.str().c_str());

        switch (interpretation.action) {
            case DRAW_FORWARD:
                writer.writeAttribute("interpretation", "draw");
                break;
            case ROTATE:
                {
                    writer.writeAttribute("interpretation", "rotate");

                    std::stringstream ss;

                    ss << interpretation.param;

                    writer.writeAttribute("param", ss.str().c_str());
                }
                break;
            case PUSH_MATRIX:
                writer.writeAttribute("interpretation", "push");
                break;
            case POP_MATRIX:
                writer.writeAttribute("interpretation", "pop");
                break;
            default:
                break;
        }

        writer.writeEndElement(); // symbol
    }
    writer.writeEndElement(); // symbols
}

void LSystem::writeParam(QXmlStreamWriter &writer, QString name, QString value)
{
    writer.writeStartElement("param");
    writer.writeAttribute("name", name);
    writer.writeAttribute("value", value);
    writer.writeEndElement(); // param
}

void LSystem::writeParams(QXmlStreamWriter &writer)
{
    writer.writeStartElement("params");

    // color-bg
    writeParam(writer, "color-bg", backgroundColor.name());

    // color-fg
    writeParam(writer, "color-fg", foregroundColor.name());

    std::stringstream ss;

    // start-x
    ss.str(std::string()); ss.clear();
    ss << startX;
    writeParam(writer, "start-x", ss.str().c_str());

    // start-y
    ss.str(std::string()); ss.clear();
    ss << startY;
    writeParam(writer, "start-y", ss.str().c_str());

    // start-rot
    ss.str(std::string()); ss.clear();
    ss << startRot;
    writeParam(writer, "start-rot", ss.str().c_str());

    // iterations
    ss.str(std::string()); ss.clear();
    ss << iterations;
    writeParam(writer, "iterations", ss.str().c_str());

    // step-length
    ss.str(std::string()); ss.clear();
    ss << stepLength;
    writeParam(writer, "step-length", ss.str().c_str());

    writer.writeEndElement(); // params
}

void LSystem::load(QFile *f)
{
    if (!f->open(QIODevice::ReadOnly | QIODevice::Text)) {
        //QMessageBox::critical(this, "Fatal total error", "Total fatal error", QMessageBox::Ok);
        return;
    }

    QXmlStreamReader xml(f);

    setDefaultState();

    while ((!xml.atEnd()) && (!xml.hasError())) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement) {
            QXmlStreamAttributes attributes = xml.attributes();

            if (xml.name() == "start") {
                parseStart(xml);
            }
            else if (xml.name() == "rule") {
                parseRule(attributes);
            }
            else if (xml.name() == "symbol") {
                parseSymbol(attributes);
            }
            else if (xml.name() == "param") {
                parseParameter(attributes);
            }
        }
    }

    xml.clear();

    emit lSystemWasChanged();
    emit startXWasChanged(startX);
    emit startYWasChanged(startY);
    emit startRotWasChanged(startRot);
    emit iterationsWasChanged(iterations);
    emit stepLengthWasChanged(stepLength);
    emit backgroundColorWasChanged(backgroundColor);
    emit foregroundColorWasChanged(foregroundColor);
}

void LSystem::parseStart(QXmlStreamReader &reader)
{
    std::string start = reader.readElementText().toStdString();

    this->start = start;
}

void LSystem::parseRule(const QXmlStreamAttributes &attributes)
{
    std::string rewriteFrom(attributes.value("from").toString().toStdString());
    std::string rewriteTo(attributes.value("to").toString().toStdString());

    rules.push_back(std::make_pair(rewriteFrom, rewriteTo));
}

void LSystem::parseSymbol(const QXmlStreamAttributes &attributes)
{
    std::string name = attributes.value("name").toString().toStdString();
    std::string interpretationS = attributes.value("interpretation").toString().toStdString();
    int param = attributes.value("param").toInt();

    CharInterpretation interpretation;

    interpretation.symbol = name.at(0);

    if (interpretationS == "draw") {
        interpretation.action = DRAW_FORWARD;
    }
    else if (interpretationS == "move") {
        interpretation.action = MOVE_FORWARD;
    }
    else if (interpretationS == "rotate") {
        interpretation.action = ROTATE;
        interpretation.param = param;
    }
    else if (interpretationS == "push") {
        interpretation.action = PUSH_MATRIX;
    }
    else if (interpretationS == "pop") {
        interpretation.action = POP_MATRIX;
    }
    else return;

    this->interpretations.push_back(interpretation);
}

void LSystem::parseParameter(const QXmlStreamAttributes &attributes)
{
    std::string name = attributes.value("name").toString().toStdString();
    QStringRef value(attributes.value("value"));

    if (name == "iterations") {
        iterations = value.toInt();
    }
    else if (name == "color-bg") {
        backgroundColor = value.toString();
    }
    else if (name == "color-fg") {
        foregroundColor = value.toString();
    }
    else if (name == "start-x") {
        startX = value.toDouble();
    }
    else if (name == "start-y") {
        startY = value.toDouble();
    }
    else if (name == "start-rot") {
        startRot = value.toInt();
    }
    else if (name == "iterations") {
        iterations = value.toInt();
    }
    else if (name == "step-length") {
        stepLength = value.toInt();
    }
}

void LSystem::setRandomColors()
{
    srand(time(NULL));

    backgroundColor.setRed(random() % 256);
    backgroundColor.setGreen(random() % 256);
    backgroundColor.setBlue(random() % 256);

    foregroundColor.setRed(random() % 256);
    foregroundColor.setGreen(random() % 256);
    foregroundColor.setBlue(random() % 256);

    emit backgroundColorWasChanged(backgroundColor);
    emit foregroundColorWasChanged(foregroundColor);
}

void LSystem::setStart(std::string start)
{
    if (start != this->start) {
        this->start = start;
        emit lSystemWasChanged();
    }
}

void LSystem::setStartX(double startX)
{
    if (startX != this->startX) {
        this->startX = startX;
        emit startXWasChanged(this->startX);
        emit lSystemWasChanged();
    }
}

void LSystem::setStartY(double startY)
{
    if (startY != this->startY) {
        this->startY = startY;
        emit startYWasChanged(this->startY);
        emit lSystemWasChanged();
    }
}

void LSystem::setStartRot(int startRot)
{
    if (startRot != this->startRot) {
        this->startRot = startRot;
        emit startRotWasChanged(this->startRot);
        emit lSystemWasChanged();
    }
}

void LSystem::setIterations(int iterations)
{
    if (iterations != this->iterations) {
        this->iterations = iterations;
        emit iterationsWasChanged(this->iterations);
        emit lSystemWasChanged();
    }
}

void LSystem::setStepLength(int stepLength)
{
    if (stepLength != this->stepLength) {
        this->stepLength = stepLength;
        emit stepLengthWasChanged(this->stepLength);
        emit lSystemWasChanged();
    }
}

void LSystem::addRule()
{
    rules.push_back(std::make_pair("", ""));
    emit lSystemWasChanged();
}

void LSystem::setRule(int i, std::string from, std::string to)
{
    if ((from != rules.at(i).first) || (to != rules.at(i).second)) {
        rules.at(i).first = from;
        rules.at(i).second = to;
        emit lSystemWasChanged();
    }
}

void LSystem::removeRule(int i)
{
    rules.erase(rules.begin() + i); emit lSystemWasChanged();
}

void LSystem::setBackgroundColor(QColor backgroundColor)
{
    if (backgroundColor.isValid() && (backgroundColor != this->backgroundColor)) {
        this->backgroundColor = backgroundColor;
        emit backgroundColorWasChanged(this->backgroundColor);
        emit lSystemWasChanged();
    }
}

void LSystem::setForegroundColor(QColor foregroundColor)
{
    if (foregroundColor.isValid() && (foregroundColor != this->foregroundColor)) {
        this->foregroundColor = foregroundColor;
        emit foregroundColorWasChanged(this->foregroundColor);
        emit lSystemWasChanged();
    }
}


void LSystem::addInterpretation()
{
    interpretations.push_back(CharInterpretation());
}


void LSystem::setInterpretationLetter(size_t i, char s)
{
    if (interpretations.at(i).symbol != s) {
        interpretations.at(i).symbol = s;
        emit lSystemWasChanged();
    }
}


void LSystem::setInterpretationAction(size_t i, CharInterpretationAction action)
{
    if (interpretations.at(i).action != action) {
        interpretations.at(i).action = action;
        emit lSystemWasChanged();
    }
}

void LSystem::setInterpretationParam(size_t i, int param)
{
    if (interpretations.at(i).param != param) {
        interpretations.at(i).param = param;
        emit lSystemWasChanged();
    }
}

void LSystem::removeInterpretation(size_t i)
{
    interpretations.erase(interpretations.begin() + i);
}


