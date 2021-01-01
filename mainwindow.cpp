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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

#include "tinyxml2.h" // For xml language files

#include "cfop.h"

using namespace grcube3;
using namespace tinyxml2;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Save default language texts
    SaveXMLDefaultLanguage();

    // Load default language texts for use in undefined texts
    LoadXMLDefaultLanguage();

    // Update cores
    ui->spinBox_Cores->setMinimum(0);
    ui->spinBox_Cores->setMaximum(DeepSearch::GetSystemCores());
    ui->spinBox_Cores->setValue(0);

    // Display language files
    QDir directory = QDir::currentPath();
    QStringList langfiles = directory.entryList(QStringList() << "*.xml" << "*.XML", QDir::Files);
    foreach(QString filename, langfiles) ui->comboBox_Language->addItem(filename);

    // No scramble text in status bar
    MainWindow::on_lineEdit_Scramble_textChanged(ui->lineEdit_Scramble->text());

    // Show credits at start
    on_pushButton_Credits_clicked();

    // Updates the reference time for estimations (with all cores)
    UpdateRefTime(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Read default texts from the application and save it to a default xml language file
void MainWindow::SaveXMLDefaultLanguage() const
{
    XMLDocument lang_xml;
    XMLNode* pRoot = lang_xml.NewElement("Root"); // Root node
    lang_xml.InsertFirstChild(pRoot);

    XMLElement* pElement;

    // Fixed texts

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_ScrambleTitle->objectName().toStdString().c_str());
    pElement->SetText(ui->label_ScrambleTitle->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_CopyScramble->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_CopyScramble->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_PasteScramble->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_PasteScramble->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_ClearScramble->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_ClearScramble->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_RandomScramble->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_RandomScramble->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_Crosses->objectName().toStdString().c_str());
    pElement->SetText(ui->label_Crosses->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Up->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Up->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Down->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Down->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Front->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Front->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Back->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Back->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Right->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Right->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->checkBox_Left->objectName().toStdString().c_str());
    pElement->SetText(ui->checkBox_Left->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_CrossDeep->objectName().toStdString().c_str());
    pElement->SetText(ui->label_CrossDeep->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_CopyReport->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_CopyReport->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_ClearReport->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_ClearReport->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_SaveReport->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_SaveReport->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_Cores->objectName().toStdString().c_str());
    pElement->SetText(ui->label_Cores->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_StartSearch->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_StartSearch->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_Language->objectName().toStdString().c_str());
    pElement->SetText(ui->label_Language->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_Credits->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_Credits->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->pushButton_License->objectName().toStdString().c_str());
    pElement->SetText(ui->pushButton_License->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_LastLayer->objectName().toStdString().c_str());
    pElement->SetText(ui->label_LastLayer->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->radioButton_1LLL->objectName().toStdString().c_str());
    pElement->SetText(ui->radioButton_1LLL->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->radioButton_2LLL->objectName().toStdString().c_str());
    pElement->SetText(ui->radioButton_2LLL->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("FixedText");
    pElement->SetAttribute("ObjectName", ui->label_PayPal->objectName().toStdString().c_str());
    pElement->SetText(ui->label_PayPal->text().toStdString().c_str());
    pRoot->InsertEndChild(pElement);

    // Messages

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "MainWindowTitle");
    pElement->SetText("CFOP Master V1.0");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "NoScramble");
    pElement->SetText("No scramble!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ScrambleSimplified");
    pElement->SetText("Scramble simplified: ");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "NewRandomScrambleCreated");
    pElement->SetText("New random scramble created");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ScrambleCopiedToClipboard");
    pElement->SetText("Scramble copied to clipboard");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ScramblePastedFromClipboard");
    pElement->SetText("Scramble pasted from clipboard");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ScrambleCleared");
    pElement->SetText("Scramble cleared");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "AllAvaliable");
    pElement->SetText("All avaliable");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "CoresWillBeUsedInTheSearch");
    pElement->SetText(" threads will be used in the search");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SingleCoreWillBeUsedInTheSearch");
    pElement->SetText("Single thread will be used in the search");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "CrossIn ");
    pElement->SetText("Cross in ");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "UpLayer");
    pElement->SetText("Up layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "DownLayer");
    pElement->SetText("Down layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "FrontLayer");
    pElement->SetText("Front layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "BackLayer");
    pElement->SetText("Back layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "RightLayer");
    pElement->SetText("Right layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "LeftLayer");
    pElement->SetText("Left layer");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "WillBeExcludedInTheSearch");
    pElement->SetText(" cross will be excluded from the search");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "WillBeIncludedInTheSearch");
    pElement->SetText(" cross will be included in the search");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "EstimatedSearchTime");
    pElement->SetText("Estimated search time: ");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SecondsUnit");
    pElement->SetText(" s");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "NoSearchAsNoLayerForCrossIsSelected");
    pElement->SetText("Please, select at least one cross layer!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchingCross");
    pElement->SetText("Searching cross...");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinishedCrossNotFound");
    pElement->SetText("Search finished, cross not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchingF2L");
    pElement->SetText("Searching F2L...");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinishedF2LNotFound");
    pElement->SetText("Search finished, F2L not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchingOLL");
    pElement->SetText("Searching OLL...");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinishedOLLNotFound");
    pElement->SetText("Search finished, OLL not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchingPLL");
    pElement->SetText("Searching PLL...");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinishedPLLNotFound");
    pElement->SetText("Search finished, PLL not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "Searching1LLL");
    pElement->SetText("Searching 1LLL...");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinished1LLLNotFound");
    pElement->SetText("Search finished, 1LLL not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SearchFinished");
    pElement->SetText("Search finished, enjoy!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ReportCopiedToTheClipboard");
    pElement->SetText("Report copied to the clipboard");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ReportCleared");
    pElement->SetText("Report cleared");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "SaveReport");
    pElement->SetText("Save report");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "TextAllFiles");
    pElement->SetText("Text (*.txt);;All Files (*)");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ReportSaved");
    pElement->SetText("Report saved");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "Error");
    pElement->SetText("Error");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "UnableToOpenFile");
    pElement->SetText("Unable to open file");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ReportNotSaved");
    pElement->SetText("Report not saved!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "ApplicationLanguageChanged");
    pElement->SetText("Application language changed");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "DefaultLanguageApplied");
    pElement->SetText("Application language change error, default language applied!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "NoCredits");
    pElement->SetText("Credits file not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "NoLicense");
    pElement->SetText("License file not found!");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "TwoLookLastLayer");
    pElement->SetText("Two-Look Last Layer (OLL + PLL) selected");
    pRoot->InsertEndChild(pElement);

    pElement = lang_xml.NewElement("Message");
    pElement->SetAttribute("Id", "OneLookLastLayer");
    pElement->SetText("One-Look Last Layer selected");
    pRoot->InsertEndChild(pElement);

    lang_xml.SaveFile("default.xml");
}

// Load the default xml language file texts
bool MainWindow::LoadXMLDefaultLanguage()
{
    DefaultLang.clear();

    XMLDocument lang_xml;

    if (lang_xml.LoadFile("default.xml") == XML_SUCCESS) // Read existing file
    {
        XMLNode* pRoot = lang_xml.FirstChild();

        if (pRoot != nullptr)
        {
            const char *objectName, *objectText, *Id, *Message;
            XMLElement* pElement = pRoot->FirstChildElement("FixedText");
            while (pElement != nullptr)
            {
                objectText = pElement->GetText();
                objectName = pElement->Attribute("ObjectName");

                DefaultLang.insert(objectName, objectText);

                pElement = pElement->NextSiblingElement("FixedText");
            }

            pElement = pRoot->FirstChildElement("Message");
            while (pElement != nullptr)
            {
                Message = pElement->GetText();
                Id = pElement->Attribute("Id");

                DefaultLang.insert(Id, Message);

                pElement = pElement->NextSiblingElement("Message");
            }
        }
        return true;
    }
    return false;
}

// Load the xml language file for the application current language
bool MainWindow::LoadXMLCurrentLanguage(const QString &lang)
{
    CurrentLang.clear();

    XMLDocument lang_xml;

    if (lang_xml.LoadFile(lang.toStdString().c_str()) == XML_SUCCESS) // Read existing file
    {
        XMLNode* pRoot = lang_xml.FirstChild();

        if (pRoot != nullptr)
        {
            const char *objectName, *objectText, *Id, *Message;
            XMLElement* pElement = pRoot->FirstChildElement("FixedText");
            while (pElement != nullptr)
            {
                objectText = pElement->GetText();
                objectName = pElement->Attribute("ObjectName");

                CurrentLang.insert(objectName, objectText);

                pElement = pElement->NextSiblingElement("FixedText");
            }

            pElement = pRoot->FirstChildElement("Message");
            while (pElement != nullptr)
            {
                Message = pElement->GetText();
                Id = pElement->Attribute("Id");

                CurrentLang.insert(Id, Message);

                pElement = pElement->NextSiblingElement("Message");
            }
        }

        // Complete the language data with the default texts
        LangMap::const_iterator i = DefaultLang.constBegin();
        while (i != DefaultLang.constEnd())
        {
            if (!CurrentLang.contains(i.key())) CurrentLang.insert(i.key(), i.value());
            ++i;
        }

        return true;
    }
    return false;
}

// Updates the fixed texts in the application
void MainWindow::UpdateFixedTexts(const LangMap& Lang)
{
    if (Lang.contains("MainWindowTitle")) setWindowTitle(Lang["MainWindowTitle"]);
    else setWindowTitle(DefaultLang["MainWindowTitle"]);

    QWidget *pWin = QApplication::activeWindow();

    LangMap::const_iterator i = Lang.constBegin();
    while (i != Lang.constEnd())
    {
        if (QWidget* widget = pWin->findChild<QWidget*>(i.key()))
        { // In this application, fixed texts are only in push buttons, labels, check boxes and radio buttons
            if(QPushButton *pb = qobject_cast<QPushButton*>(widget)) pb->setText(i.value());
            else if(QLabel *lb = qobject_cast<QLabel*>(widget)) lb->setText(i.value());
            else if(QCheckBox *cb = qobject_cast<QCheckBox*>(widget)) cb->setText(i.value());
            else if(QRadioButton *rb = qobject_cast<QRadioButton*>(widget)) rb->setText(i.value());
        }
        ++i;
    }
}

// Calculates the reference time for estimations
void MainWindow::UpdateRefTime(int cores)
{
    Algorithm RefA("B' R' F L' U B' L B D B2 D2 B R' D' U' B' D2 F B' U L U B2 R2 F2");

    CFOP RefSearch(RefA, cores);

    std::vector<PiecesGroups> Crosses;
    Crosses.push_back(PiecesGroups::C_U);
    Crosses.push_back(PiecesGroups::C_D);
    Crosses.push_back(PiecesGroups::C_F);
    Crosses.push_back(PiecesGroups::C_B);
    Crosses.push_back(PiecesGroups::C_R);
    Crosses.push_back(PiecesGroups::C_L);

    RefSearch.SearchCross(4, Crosses);

    RefTime = RefSearch.GetCrossTime();
}

void MainWindow::on_lineEdit_Scramble_textChanged(const QString &scrInput)
{
    if (scrInput.isEmpty())
    {
        ui->pushButton_CopyScramble->setDisabled(true);
        ui->pushButton_ClearScramble->setDisabled(true);
        ui->pushButton_StartSearch->setDisabled(true);

        ui->statusBar->showMessage(CurrentLang["NoScramble"]);
    }
    else
    {
        ui->pushButton_CopyScramble->setEnabled(true);
        ui->pushButton_ClearScramble->setEnabled(true);
        ui->pushButton_StartSearch->setEnabled(true);

        Algorithm A(ui->lineEdit_Scramble->text().toStdString().c_str());
        A = A.GetSimplified();
        A = A.GetWithoutTurns();
        while (A.Shrink());
        ui->statusBar->showMessage(CurrentLang["ScrambleSimplified"] + QString::fromStdString(A.ToString()));
    }
}

void MainWindow::on_pushButton_RandomScramble_clicked()
{
    Algorithm A(ui->spinBox_ScrambleLength->value());
    ui->lineEdit_Scramble->setText(QString::fromStdString(A.ToString()));
    ui->statusBar->showMessage(CurrentLang["NewRandomScrambleCreated"]);
}

void MainWindow::on_pushButton_CopyScramble_clicked()
{
    QApplication::clipboard()->setText(ui->lineEdit_Scramble->text());
    ui->statusBar->showMessage(CurrentLang["ScrambleCopiedToClipboard"]);
}

void MainWindow::on_pushButton_PasteScramble_clicked()
{
    ui->lineEdit_Scramble->setText(QApplication::clipboard()->text());
    ui->statusBar->showMessage(CurrentLang["ScramblePastedFromClipboard"]);
}

void MainWindow::on_pushButton_ClearScramble_clicked()
{
    ui->lineEdit_Scramble->clear();
    ui->statusBar->showMessage(CurrentLang["ScrambleCleared"]);
}

void MainWindow::on_spinBox_Cores_valueChanged(int cores)
{
    if (cores == 0) ui->statusBar->showMessage(CurrentLang["AllAvaliable"] + CurrentLang["CoresWillBeUsedInTheSearch"]);
    else if (cores == 1) ui->statusBar->showMessage(CurrentLang["SingleCoreWillBeUsedInTheSearch"]);
    else ui->statusBar->showMessage(QString::number(cores) + CurrentLang["CoresWillBeUsedInTheSearch"]);

    UpdateRefTime(cores);
}

void MainWindow::on_checkBox_Up_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["UpLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["UpLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_checkBox_Down_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["DownLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["DownLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_checkBox_Front_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["FrontLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["FrontLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_checkBox_Back_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["BackLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["BackLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_checkBox_Right_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["RightLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["RightLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_checkBox_Left_stateChanged(int stat)
{
    if (stat == 0) ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["LeftLayer"] + CurrentLang["WillBeExcludedInTheSearch"]);
    else ui->statusBar->showMessage(CurrentLang["Cross in "] + CurrentLang["LeftLayer"] + CurrentLang["WillBeIncludedInTheSearch"]);
}

void MainWindow::on_spinBox_Cross_valueChanged(int deep)
{
    UpdateRefTime(ui->spinBox_Cores->value());
    double EstimatedTime = RefTime;
    for (int n = 4; n < deep; n++) EstimatedTime *= 15.0; // Cross estimated search time
    EstimatedTime += RefTime * 300.0; // F2L estimated search time

    ui->statusBar->showMessage(CurrentLang["EstimatedSearchTime"] + QString::number(static_cast<int>(EstimatedTime)) + CurrentLang["SecondsUnit"]);
}

void MainWindow::on_pushButton_StartSearch_clicked()
{
    on_spinBox_Cross_valueChanged(ui->spinBox_Cross->value()); // Show estimated search time

    // Clear output
    ui->textEdit_Report->clear();
    ui->pushButton_CopyReport->setDisabled(true);
    ui->pushButton_ClearReport->setDisabled(true);
    ui->pushButton_SaveReport->setDisabled(true);
    ui->pushButton_StartSearch->setDisabled(true);

    // Read scramble
    Algorithm Scramble(ui->lineEdit_Scramble->text().toStdString().c_str());
    Scramble = Scramble.GetSimplified();
    Scramble = Scramble.GetWithoutTurns();
    while (Scramble.Shrink());

    // Read the allowed layers for cross
    std::vector<PiecesGroups> Crosses;
    if (ui->checkBox_Up->isChecked()) Crosses.push_back(PiecesGroups::C_U);
    if (ui->checkBox_Down->isChecked()) Crosses.push_back(PiecesGroups::C_D);
    if (ui->checkBox_Front->isChecked()) Crosses.push_back(PiecesGroups::C_F);
    if (ui->checkBox_Back->isChecked()) Crosses.push_back(PiecesGroups::C_B);
    if (ui->checkBox_Right->isChecked()) Crosses.push_back(PiecesGroups::C_R);
    if (ui->checkBox_Left->isChecked()) Crosses.push_back(PiecesGroups::C_L);
    if (Crosses.empty())
    {
        ui->statusBar->showMessage(CurrentLang["NoSearchAsNoLayerForCrossIsSelected"]);
        ui->pushButton_StartSearch->setEnabled(true);
        return;
    }

    // Create search
    CFOP SearchCFOP(Scramble);

    // Start cross search
    ui->textEdit_Report->append(CurrentLang["SearchingCross"]);
    qApp->processEvents();

    if (!SearchCFOP.SearchCross(ui->spinBox_Cross->value(), Crosses))
    {
        ui->statusBar->showMessage(CurrentLang["SearchFinishedCrossNotFound"]);
        ui->textEdit_Report->clear();
        ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
        ui->pushButton_CopyReport->setEnabled(true);
        ui->pushButton_ClearReport->setEnabled(true);
        ui->pushButton_SaveReport->setEnabled(true);
        ui->pushButton_StartSearch->setEnabled(true);
        return;
    }

    // Start F2L search
    ui->textEdit_Report->append(CurrentLang["SearchingF2L"]);
    qApp->processEvents();

    if (!SearchCFOP.SearchF2L())
    {
        ui->statusBar->showMessage(CurrentLang["SearchFinishedF2LNotFound"]);
        ui->textEdit_Report->clear();
        ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
        ui->pushButton_CopyReport->setEnabled(true);
        ui->pushButton_ClearReport->setEnabled(true);
        ui->pushButton_SaveReport->setEnabled(true);
        ui->pushButton_StartSearch->setEnabled(true);
        return;
    }

    if (ui->radioButton_2LLL->isChecked()) // OLL + PLL
    {
        // Start OLL search
        ui->textEdit_Report->append(CurrentLang["SearchingOLL"]);
        qApp->processEvents();

        if (!SearchCFOP.SearchOLL())
        {
            ui->statusBar->showMessage(CurrentLang["SearchFinishedOLLNotFound"]);
            ui->textEdit_Report->clear();
            ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
            ui->pushButton_CopyReport->setEnabled(true);
            ui->pushButton_ClearReport->setEnabled(true);
            ui->pushButton_SaveReport->setEnabled(true);
            ui->pushButton_StartSearch->setEnabled(true);
            return;
        }

        // Start PLL search
        ui->textEdit_Report->append(CurrentLang["SearchingPLL"]);
        qApp->processEvents();

        if (!SearchCFOP.SearchPLL())
        {
            ui->statusBar->showMessage(CurrentLang["SearchFinishedPLLNotFound"]);
            ui->textEdit_Report->clear();
            ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
            ui->pushButton_CopyReport->setEnabled(true);
            ui->pushButton_ClearReport->setEnabled(true);
            ui->pushButton_SaveReport->setEnabled(true);
            ui->pushButton_StartSearch->setEnabled(true);
            return;
        }
    }
    else // 1LLL
    {
        // Start 1LLL search
        ui->textEdit_Report->append(CurrentLang["Searching1LLL"]);
        qApp->processEvents();

        if (!SearchCFOP.Search1LLL())
        {
            ui->statusBar->showMessage(CurrentLang["SearchFinished1LLLNotFound"]);
            ui->textEdit_Report->clear();
            ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
            ui->pushButton_CopyReport->setEnabled(true);
            ui->pushButton_ClearReport->setEnabled(true);
            ui->pushButton_SaveReport->setEnabled(true);
            ui->pushButton_StartSearch->setEnabled(true);
            return;
        }
    }

    ui->textEdit_Report->clear();
    ui->textEdit_Report->append(QString::fromStdString(SearchCFOP.GetReport()));
    ui->statusBar->showMessage(CurrentLang["SearchFinished"]);
    ui->pushButton_CopyReport->setEnabled(true);
    ui->pushButton_ClearReport->setEnabled(true);
    ui->pushButton_SaveReport->setEnabled(true);
    ui->pushButton_StartSearch->setEnabled(true);
}

void MainWindow::on_pushButton_CopyReport_clicked()
{
    QApplication::clipboard()->setText(ui->textEdit_Report->toPlainText());
    ui->statusBar->showMessage(CurrentLang["ReportCopiedToTheClipboard"]);
}

void MainWindow::on_pushButton_ClearReport_clicked()
{
    // Clear output
    ui->textEdit_Report->clear();
    ui->pushButton_CopyReport->setDisabled(true);
    ui->pushButton_ClearReport->setDisabled(true);
    ui->pushButton_SaveReport->setDisabled(true);
    ui->statusBar->showMessage(CurrentLang["ReportCleared"]);
}

void MainWindow::on_pushButton_SaveReport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr(CurrentLang["SaveReport"].toStdString().c_str()), "", tr(CurrentLang["TextAllFiles"].toStdString().c_str()));

    if (fileName.isEmpty()) return;
    else
    {
        QFile file(fileName);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << ui->textEdit_Report->toPlainText();
            file.flush();
            file.close();
            ui->statusBar->showMessage(CurrentLang["ReportSaved"]);
        }
        else
        {
            QMessageBox::information(this, tr(CurrentLang["Error"].toStdString().c_str()), tr(CurrentLang["UnableToOpenFile"].toStdString().c_str()));
            ui->statusBar->showMessage(CurrentLang["ReportNotSaved"]);
            return;
        }
    }
}

void MainWindow::on_comboBox_Language_currentIndexChanged(const QString &langfile)
{
    if (LoadXMLCurrentLanguage(langfile))
    {
        UpdateFixedTexts(CurrentLang);
        ui->statusBar->showMessage(CurrentLang["ApplicationLanguageChanged"]);
    }
    else
    {
        UpdateFixedTexts(DefaultLang);
        ui->statusBar->showMessage(CurrentLang["DefaultLanguageApplied"]);
    }
}

void MainWindow::on_pushButton_Credits_clicked()
{
    QFile file("CREDITS");
    QString credits_text;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        credits_text.append(stream.readAll());
    }
    else credits_text = CurrentLang["NoCredits"];

    ui->textEdit_Report->clear();
    ui->textEdit_Report->setText(credits_text);
    ui->pushButton_CopyReport->setEnabled(true);
    ui->pushButton_SaveReport->setEnabled(true);
    ui->pushButton_ClearReport->setEnabled(true);
}

void MainWindow::on_pushButton_License_clicked()
{
    QFile file("COPYING");
    QString license_text;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        license_text.append(stream.readAll());
    }
    else license_text = CurrentLang["NoLicense"];

    ui->textEdit_Report->clear();
    ui->textEdit_Report->setText(license_text);
    ui->pushButton_CopyReport->setEnabled(true);
    ui->pushButton_SaveReport->setEnabled(true);
    ui->pushButton_ClearReport->setEnabled(true);
}

void MainWindow::on_radioButton_2LLL_toggled(bool checked)
{
    if (checked) ui->statusBar->showMessage(CurrentLang["TwoLookLastLayer"]);
    else ui->statusBar->showMessage(CurrentLang["OneLookLastLayer"]);
}
