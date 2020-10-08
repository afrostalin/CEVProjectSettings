// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#pragma once

#include <QtViewPane.h>
#include <QAbstractItemModel>
#include <QAdvancedPropertyTreeLegacy.h>
#include <Controls/QObjectTreeWidget.h>
#include <QControls.h>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>

struct SProjectSettingsPage;

class QProjectSettingsPage : public QWidget
{
	Q_OBJECT
public:
	QProjectSettingsPage(SProjectSettingsPage* pPreferencePage, QWidget* pParent = nullptr);
	QProjectSettingsPage(std::vector<SProjectSettingsPage*> preferences, const char* path, QWidget* pParent = nullptr);
	~QProjectSettingsPage();

private:
	void InitUI();
	void OnPreferenceChanged();

	void ConnectPreferences();
	void DisconnectPreferences();

private slots:
	void OnPropertyChanged();
	void OnResetToDefault();

private:
	QAdvancedPropertyTreeLegacy* m_pPropertyTree = nullptr;
	std::vector<SProjectSettingsPage*> m_preferencePages;
	const string m_path;
};

class QProjectSettingsDialog : public CDockableWidget
{
public:
	QProjectSettingsDialog(QWidget* pParent = nullptr);
	~QProjectSettingsDialog();
public:
	// CDockableWidget
	virtual const char* GetPaneTitle() const override { return "Project settings"; }
	virtual QRect       GetPaneRect() override { return QRect(0, 0, 800, 1200); }
	//~CDockableWidget
protected:
	void OnPreferencePageSelected(const char* path);
	void OnPreferencesReset();

private:
	QContainer* m_pContainer = nullptr;
	QSplitter* m_pSplitter = nullptr;
	QObjectTreeWidget* m_pTreeView = nullptr;
	string             m_currPath;
};