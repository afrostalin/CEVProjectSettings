// Copyright (C) 2020 Space Raccoon Game Studio. All rights reserved. Contacts: <business@space-raccoon.com>
// Created by AfroStalin

#include "StdAfx.h"
#include "ProjectSettingsDialog.h"
#include "ProjectSettings.h"

struct SPreferencePagesContainer
{
	SPreferencePagesContainer(const std::vector<SProjectSettingsPage*>& preferences)
		: m_preferences(preferences)
	{
	}

	virtual ~SPreferencePagesContainer() {}

	virtual bool Serialize(yasli::Archive& ar)
	{
		for (SProjectSettingsPage* pPreferencePage : m_preferences)
		{
			if (pPreferencePage->IsVisible())
			{
				pPreferencePage->Serialize(ar);
			}
		}

		return true;
	}

private:
	std::vector<SProjectSettingsPage*> m_preferences;
};

QProjectSettingsPage::QProjectSettingsPage(std::vector<SProjectSettingsPage*> preferencesPages, const char* path, QWidget* pParent /* = nullptr*/)
	: QWidget(pParent)
	, m_preferencePages(preferencesPages)
	, m_path(path)
{
	InitUI();

	SPreferencePagesContainer* pContainer = new SPreferencePagesContainer(preferencesPages);
	m_pPropertyTree->attach(yasli::Serializer(*pContainer));
	m_pPropertyTree->expandAll();
}

QProjectSettingsPage::QProjectSettingsPage(SProjectSettingsPage* pPreferencePage, QWidget* pParent /*= nullptr*/)
	: QWidget(pParent)
	, m_preferencePages({ pPreferencePage })
	, m_path(pPreferencePage->GetPath())
{
	InitUI();

	m_pPropertyTree->attach(yasli::Serializer(*pPreferencePage));
	m_pPropertyTree->expandAll();
}

QProjectSettingsPage::~QProjectSettingsPage()
{
	DisconnectPreferences();
}

void QProjectSettingsPage::InitUI()
{
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->setMargin(0);
	pMainLayout->setSpacing(0);

	m_pPropertyTree = new QAdvancedPropertyTreeLegacy("Properties", this);
	m_pPropertyTree->setShowContainerIndices(true);
	connect(m_pPropertyTree, &QPropertyTreeLegacy::signalChanged, this, &QProjectSettingsPage::OnPropertyChanged);
	pMainLayout->addWidget(m_pPropertyTree);
	ConnectPreferences();

	QHBoxLayout* pActionLayout = new QHBoxLayout();
	pActionLayout->setSpacing(0);
	pActionLayout->setContentsMargins(0, 4, 4, 4);
	pActionLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
	QPushButton* pResetButton = new QPushButton("Reset to Default");
	connect(pResetButton, &QPushButton::clicked, this, &QProjectSettingsPage::OnResetToDefault);
	pActionLayout->addWidget(pResetButton);
	pMainLayout->addLayout(pActionLayout);

	setLayout(pMainLayout);
}

void QProjectSettingsPage::OnPreferenceChanged()
{
	m_pPropertyTree->revertNoninterrupting();
}

void QProjectSettingsPage::ConnectPreferences()
{
	for (SProjectSettingsPage* pPreferencePage : m_preferencePages)
	{
		pPreferencePage->signalSettingsChanged.Connect(this, &QProjectSettingsPage::OnPreferenceChanged);
	}
}

void QProjectSettingsPage::DisconnectPreferences()
{
	for (SProjectSettingsPage* pPreferencePage : m_preferencePages)
	{
		pPreferencePage->signalSettingsChanged.DisconnectObject(this);
	}
}

void QProjectSettingsPage::OnPropertyChanged()
{
	CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->Save();
}

void QProjectSettingsPage::OnResetToDefault()
{
	CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->Reset(m_path);
}

QProjectSettingsDialog::QProjectSettingsDialog(QWidget* pParent /*= nullptr*/)
	: CDockableWidget(pParent)
{
	QVBoxLayout* pMainLayout = new QVBoxLayout();

	m_pTreeView = new QObjectTreeWidget();
	m_pTreeView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

	const char* szGeneral = "General";
	CProjectSettings* pPreferences = CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings();
	const std::map<string, std::vector<SProjectSettingsPage*>>& preferences = pPreferences->GetPages();

	for (auto ite = preferences.begin(); ite != preferences.end(); ++ite)
	{
		auto moduleIdx = ite->first.find_last_of("/");
		string module = ite->first.Mid(moduleIdx + 1, ite->first.size() - moduleIdx);
		m_pTreeView->AddEntry(ite->first, ite->first, module == szGeneral ? "aGeneral" : "z" + module);
	}

	for (const auto& it : preferences)
	{
		for (const auto& page : it.second)
		{
			if (!page->IsVisible())
			{
				m_pTreeView->RemoveEntry(it.first, it.first);
			}
		}
	}

	m_pTreeView->ExpandAll();

	// Create empty preference  page container
	m_pContainer = new QContainer();
	m_pContainer->setObjectName("QPanel");
	m_pSplitter = new QSplitter(Qt::Horizontal);
	m_pSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	m_pSplitter->addWidget(m_pTreeView);
	m_pSplitter->addWidget(m_pContainer);
	pMainLayout->addWidget(m_pSplitter);
	m_pSplitter->setSizes({ m_pTreeView->sizeHint().width(), GetPaneRect().width() });

	m_pTreeView->signalOnClickFile.Connect(this, &QProjectSettingsDialog::OnPreferencePageSelected);
	pPreferences->signalSettingsReset.Connect(this, &QProjectSettingsDialog::OnPreferencesReset);

	setLayout(pMainLayout);
}

QProjectSettingsDialog::~QProjectSettingsDialog()
{
	m_pTreeView->signalOnClickFile.DisconnectObject(this);
	CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->signalSettingsReset.DisconnectObject(this);
}

void QProjectSettingsDialog::OnPreferencePageSelected(const char* path)
{
	m_pContainer->SetChild(CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->GetPageWidget(path));
	m_currPath = path;
}

void QProjectSettingsDialog::OnPreferencesReset()
{
	m_pContainer->SetChild(CCEVProjectSettingsPlugin::GetInstance()->GetProjectSettings()->GetPageWidget(m_currPath));
}