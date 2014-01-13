
#include "lsystem.h"
#include <iostream>

LSystem::LSystem()
{
    setDefaultState();
}

void LSystem::setDefaultState()
{
    start = "";
    rules.clear();
    interpretation.clear();
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

    rules.insert(std::make_pair(rewriteFrom, rewriteTo));
}

void LSystem::parseSymbol(const QXmlStreamAttributes &attributes)
{
    std::string name = attributes.value("name").toString().toStdString();
    std::string interpretationS = attributes.value("interpretation").toString().toStdString();
    int param = attributes.value("param").toInt();

    CharInterpretation interpretation;

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

    this->interpretation.insert(std::make_pair(name[0],interpretation));
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
}
