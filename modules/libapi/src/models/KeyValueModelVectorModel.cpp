#include <QDebug>
#include <QtQml/QQmlEngine>

#include "api/models/KeyValueModelVectorModel.h"

namespace api
{
namespace models
{

KeyValueModelVectorModel::KeyValueModelVectorModel(QObject* parent) : QAbstractItemModel(parent)
{
}

void KeyValueModelVectorModel::appendModel(QObject* model)
{
	if (!model)
	{
		qCritical() << "Appended KeyValueModel is null";
		return;
	}

	const auto kvModel = qobject_cast<KeyValueModel*>(model);

	if (!kvModel)
	{
		qCritical() << "KeyValueModelVectorModel expected KeyValueModel";
		return;
	}

	// emit layoutAboutToBeChanged();

	const auto currentRowCount = rowCount();
	beginInsertRows({}, currentRowCount, currentRowCount + kvModel->rowCount() - 1);

	kvModel->setParent(this);
	QQmlEngine::setObjectOwnership(kvModel, QQmlEngine::CppOwnership);
	models_.push_back(kvModel);

	endInsertRows();

	// emit layoutChanged();
}

int KeyValueModelVectorModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

QVariant KeyValueModelVectorModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		qWarning() << "KeyValueModelVectorModel index is not valid";
		return {};
	}

	if (index.column() != 0 || index.row() < 0)
	{
		qWarning() << "KeyValueModelVectorModel index is out of range";
		return {};
	}

	if (role < Qt::UserRole)
	{
		qDebug() << "KeyValueModelVectorModel role is not user";
		return {};
	}

	auto model = models_.begin();
	int highBoundary = 0;
	for (; model != models_.end(); ++model)
	{
		highBoundary += (*model)->rowCount();
		if (index.row() < highBoundary)
		{
			break;
		}
	}

	if (model == models_.end())
	{
		qCritical() << "KeyValueModelVectorModel row is higher than summ of models' row count";
		return {};
	}

	const auto lowBoundary = highBoundary - (*model)->rowCount();

	return (*model)->data((*model)->index(index.row() - lowBoundary, 0, {}), role);
}

QModelIndex KeyValueModelVectorModel::index(int row, int column, const QModelIndex& parent) const
{
	return createIndex(row, column);
}

QModelIndex KeyValueModelVectorModel::parent(const QModelIndex& child) const
{
	return {};
}

QHash<int, QByteArray> KeyValueModelVectorModel::roleNames() const
{
	QHash<int, QByteArray> hashMap;

	for (const auto& model : models_)
	{
		hashMap.unite(model->roleNames());
	}

	QHash<int, QByteArray> uniqueMap;

	for (const auto& key : hashMap.uniqueKeys())
	{
		uniqueMap[key] = hashMap[key];
	}

	return uniqueMap;
}

int KeyValueModelVectorModel::rowCount(const QModelIndex& parent) const
{
	int count = 0;

	for (const auto& model : models_)
	{
		count += model->rowCount();
	}

	return count;
}

} // namespace models
} // namespace api
