#ifndef GRAPHICSSIZEWALL_H
#define GRAPHICSSIZEWALL_H

#include <QDialog>
#include <diagramview.h>

namespace Ui {
class GraphicsSizeWall;
}

class GraphicsSizeWall : public QDialog
{
    Q_OBJECT
    
public:
    enum AlignmentType{
        ALIGNMENT_ANGLE     = 1,
        ALIGNMENT_LENGTH    = 2
    };
    explicit GraphicsSizeWall(DiagramView *diagramView,AlignmentType type,QWidget *parent = 0);
    ~GraphicsSizeWall();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GraphicsSizeWall *ui;
    DiagramView *diagramView;
    GraphicsSizeWall::AlignmentType type;
};

#endif // GRAPHICSSIZEWALL_H
