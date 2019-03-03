#include <QDebug>

#include "api/models/KeyValueModel.h"

namespace api
{
namespace models
{

KeyValueModel::KeyValueModel(QObject* parent) : QAbstractItemModel(parent)
{
}

KeyValueModel::ModelType KeyValueModel::GetData() const
{
	return data_;
}

void KeyValueModel::SetData(const ModelType& data)
{
	data_ = data;

	keys_.clear();

	for (const auto& item : data_)
	{
		for (const auto& kv : item)
		{
			keys_.insert(kv.first);
		}
	}
}

int KeyValueModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

QVariant KeyValueModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		qWarning() << "KeyValueModel index is not valid";
		return {};
	}

	if (index.column() != 0 || index.row() < 0 || index.row() >= data_.size())
	{
		qWarning() << "KeyValueModel index is out of range";
		return {};
	}

	if (role < Qt::UserRole)
	{
		qDebug() << "KeyValueModel role sis not user";
		return {};
	}

	const auto roleName = *(keys_.begin() + (role - Qt::UserRole));
	const auto& item = data_[index.row()];

	const auto keyIter = std::find_if(
		item.begin(), item.end(), [&roleName](const auto& val) { return val.first == roleName; });

	if (keyIter == item.end())
	{
		qWarning() << "KeyValueModel role value was not found";
		return {};
	}

	return keyIter->second;
}

QModelIndex KeyValueModel::index(int row, int column, const QModelIndex& parent) const
{
	return createIndex(row, column);
}

QModelIndex KeyValueModel::parent(const QModelIndex& child) const
{
	return {};
}

QHash<int, QByteArray> KeyValueModel::roleNames() const
{
	QHash<int, QByteArray> hashMap;

	for (const auto& value : keys_)
	{
		hashMap[Qt::UserRole + hashMap.size()] = value.toUtf8();
	}

	return hashMap;
}

int KeyValueModel::rowCount(const QModelIndex& parent) const
{
	return data_.size();
}

QVariantMap KeyValueModel::getItemMapByIndex(const int index) const
{
	if (index < 0 || index >= data_.size())
	{
		qCritical() << "Index " << index << " is out of range of " << data_.size()
					<< " key-value model";
		return {};
	}

	QVariantMap map;

	for (const auto& kv : data_[index])
	{
		map[kv.first] = kv.second;
	}

	return map;
}

} // namespace models
} // namespace api
