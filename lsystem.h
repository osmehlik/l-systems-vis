
#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <QtGui>
#include <string>

// Possible actions in CharInterpretationMap
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
    CharInterpretationAction action;
    int param;
} CharInterpretation;

// CharInterpretationMap describes what action each character describes.
typedef std::map<char, CharInterpretation> CharInterpretationMap;

struct LSystem
{
    std::string start;

    // String rewriting rules.
    typedef std::map<std::string, std::string> Rules;

    Rules rules;

    double startX; // between 0 and 1, 0 = left edge, 1 = right edge
    double startY; // between 0 and 1, 0 = top edge, 1 = bottom edge
    int startRot;
    int iterations;
    int stepLength; // length of step when moving or drawing forward

    QColor backgroundColor;
    QColor foregroundColor;
    std::string evolve(int iterations);

    CharInterpretationMap interpretation;

protected:
    void parseStart(QXmlStreamReader &reader);
    void parseRule(const QXmlStreamAttributes &attributes);
    void parseSymbol(const QXmlStreamAttributes &attributes);
    void parseParameter(const QXmlStreamAttributes &attributes);

public:
    LSystem();
    void load(QFile *f);
    void setDefaultState();
    void setRandomColors();
};

#endif // LSYSTEM_H
