#ifndef ACCEPTRESULT_HPP
#define ACCEPTRESULT_HPP

#include <QDialog>

namespace Ui { class AcceptResult; }
class AcceptResult : public QDialog
{
    Q_OBJECT

private:
    Ui::AcceptResult *ui;
    unsigned int m_time_sec;

    void set_styles();

private slots:
    void on_okButton_clicked();

public:
    explicit AcceptResult(unsigned int time_sec, QWidget *parent = nullptr);
    ~AcceptResult();
};

#endif // ACCEPTRESULT_HPP
