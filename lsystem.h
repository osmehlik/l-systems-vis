
#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <QtGui>
#include <string>
#include <vector>
#include <QObject>

typedef enum
{
    MOVE_FORWARD,
    DRAW_FORWARD,
    ROTATE,
    PUSH_MATRIX,
    POP_MATRIX
} CharInterpretationAction;

typedef struct
{
    char symbol;
    CharInterpretationAction action;
    int param;
} CharInterpretation;

// What action each character describes.
typedef std::vector<CharInterpretation > CharInterpretations;

// String rewriting rules.
typedef std::vector<std::pair<std::string, std::string> > Rules;

class LSystem : public QObject
{
    Q_OBJECT

private:
    std::string start; // initial string

    Rules rules; // string rewriting rules
    CharInterpretations interpretations; // how to interpret chars in string

    double startX; // between 0 and 1, 0 = left edge, 1 = right edge
    double startY; // between 0 and 1, 0 = top edge, 1 = bottom edge
    int startRot;
    int iterations;
    int stepLength; // length of step when moving or drawing forward

    QColor backgroundColor;
    QColor foregroundColor;

protected:
    void writeStart(QXmlStreamWriter &writer);
    void writeRules(QXmlStreamWriter &writer);
    void writeSymbols(QXmlStreamWriter &writer);
    void writeParams(QXmlStreamWriter &writer);
    void writeParam(QXmlStreamWriter &writer, QString name, QString value);

    void parseStart(QXmlStreamReader &reader);
    void parseRule(const QXmlStreamAttributes &attributes);
    void parseSymbol(const QXmlStreamAttributes &attributes);
    void parseParameter(const QXmlStreamAttributes &attributes);

public:
    //LSystem() {}
    Q_INVOKABLE explicit LSystem(QObject *parent=0);
    ~LSystem();

public:

    void load(QFile *f);
    void save(QFile *f);
    void setDefaultState();
    void setRandomColors();
    std::string evolve(int iterations);

    // getters

    inline std::string getStart() { return start;      }
    inline double getStartX()     { return startX;     }
    inline double getStartY()     { return startY;     }
    inline int getStartRot()      { return startRot;   }
    inline int getIterations()    { return iterations; }
    inline int getStepLength()    { return stepLength; }

    inline QColor getBackgroundColor() { return backgroundColor; }
    inline QColor getForegroundColor() { return foregroundColor; }

    inline size_t getNumRules() { return rules.size(); }
    inline std::string getRuleFrom(size_t i) { return rules.at(i).first;  }
    inline std::string getRuleTo(size_t i)   { return rules.at(i).second; }

    inline size_t getNumInterpretations() { return interpretations.size(); }
    inline const CharInterpretation& getInterpretation(size_t i) { return interpretations.at(i); }
    inline char getInterpretationSymbol(size_t i) { return interpretations.at(i).symbol; }
    inline CharInterpretationAction getInterpretationAction(size_t i) { return interpretations.at(i).action; }
    inline int getInterpretationParam(size_t i) { return interpretations.at(i).param; }

signals:
    void lSystemWasChanged();
    void startXWasChanged(double);
    void startYWasChanged(double);
    void startRotWasChanged(int);
    void iterationsWasChanged(int);
    void stepLengthWasChanged(int);
    void backgroundColorWasChanged(QColor);
    void foregroundColorWasChanged(QColor);

    // setters

public slots:

    void setStart(std::string start);
    void setStartX(double startX);
    void setStartY(double startY);
    void setStartRot(int startRot);
    void setIterations(int iterations);
    void setStepLength(int stepLength);
    void addRule();

    void setRule(int i, std::string from, std::string to);
    void removeRule(int i);
    void setBackgroundColor(QColor backgroundColor);
    void setForegroundColor(QColor foregroundColor);

    void addInterpretation();
    void setInterpretationLetter(size_t i, char s);
    void setInterpretationAction(size_t i, CharInterpretationAction action);
    void setInterpretationParam(size_t i, int param);
    void removeInterpretation(size_t i);
};

#endif // LSYSTEM_H
