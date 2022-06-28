#include "ModelUtil.h"

#include <QAbstractItemModel>

ModelUtil::ModelUtil(QObject *parent)
    : QObject{parent}
{

}

int ModelUtil::getRoleByName(const QString &roleName, QObject *model) const
{
	if (model == nullptr) {
		return -1;
	}
	QAbstractItemModel *castedModel = qobject_cast<QAbstractItemModel *>(model);
	if (!castedModel) {
		return -1;
	}
	QHash<int, QByteArray> roles = castedModel->roleNames();
	return roles.key(roleName.toLatin1(), -1);
}

QObject *modelutil_create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
	Q_UNUSED(jsEngine)
	return new ModelUtil(qmlEngine);
}
