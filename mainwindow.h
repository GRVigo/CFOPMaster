/*  This file is part of "CFOP Master"

    Copyright (C) 2020 German Ramos Rodriguez

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    German Ramos Rodriguez
    Vigo, Spain
    grvigo@hotmail.com
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

using LangMap = QMap<QString, QString>;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_Scramble_textChanged(const QString &);

    void on_pushButton_RandomScramble_clicked();

    void on_pushButton_CopyScramble_clicked();

    void on_pushButton_PasteScramble_clicked();

    void on_pushButton_ClearScramble_clicked();

    void on_spinBox_Cores_valueChanged(int);

    void on_checkBox_Up_stateChanged(int);

    void on_checkBox_Down_stateChanged(int);

    void on_checkBox_Front_stateChanged(int);

    void on_checkBox_Back_stateChanged(int);

    void on_checkBox_Right_stateChanged(int);

    void on_checkBox_Left_stateChanged(int);

    void on_spinBox_Cross_valueChanged(int);

    void on_pushButton_StartSearch_clicked();

    void on_pushButton_CopyReport_clicked();

    void on_pushButton_ClearReport_clicked();

    void on_pushButton_SaveReport_clicked();

    void on_comboBox_Language_currentIndexChanged(const QString &arg1);

    void on_pushButton_Credits_clicked();

    void on_pushButton_License_clicked();

    void on_radioButton_2LLL_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    double RefTime;

    LangMap DefaultLang, CurrentLang;

    void SaveXMLDefaultLanguage() const;
    bool LoadXMLDefaultLanguage();
    bool LoadXMLCurrentLanguage(const QString &);

    void UpdateFixedTexts(const LangMap&);

    void UpdateRefTime(int);
};
#endif // MAINWINDOW_H
