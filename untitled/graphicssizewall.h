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
    explicit GraphicsSizeWall(DiagramView *diagramView,QWidget *parent = 0);
    ~GraphicsSizeWall();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GraphicsSizeWall *ui;
    DiagramView *diagramView;
};

#endif // GRAPHICSSIZEWALL_H
