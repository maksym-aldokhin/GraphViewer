#pragma once

#include <QObject>
#include <QJSEngine>
#include <QQmlEngine>

class ModelUtil : public QObject
{
	Q_OBJECT
public:
	explicit ModelUtil(QObject *parent = nullptr);

	Q_INVOKABLE int getRoleByName(const QString &roleName, QObject *model) const;
};

QObject *modelutil_create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);
