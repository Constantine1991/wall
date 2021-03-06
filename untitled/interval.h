#ifndef INTERVAL_H
#define INTERVAL_H

#include <QMainWindow>

namespace Ui {
class Interval;
}

class Interval : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Interval(QWidget *parent = 0);
    ~Interval();
signals:
    void setInterval(float interval,bool empty);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::Interval *ui;
    bool apply;
};

#endif // INTERVAL_H
