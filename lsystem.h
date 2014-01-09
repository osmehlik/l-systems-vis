#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <QtGui>
#include <string>

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

typedef std::map<char, CharInterpretation> CharInterpretationMap;

struct LSystem
{
    std::string start;
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

public:
    LSystem();
    void load(QFile *f);
    void clear();
};

#endif // LSYSTEM_H
