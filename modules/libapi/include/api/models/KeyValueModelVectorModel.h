#pragma once

#include "api/models/KeyValueModel.h"

#include <QDebug>

namespace api
{
namespace models
{

class KeyValueModelVectorModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	KeyValueModelVectorModel(QObject* parent = nullptr);

public:
	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent) const override;
	QModelIndex parent(const QModelIndex& child) const override;
	QHash<int, QByteArray> roleNames() const override;
	int rowCount(const QModelIndex& parent = {}) const override;

public slots:
	void appendModel(QObject* model);

private:
	QVector<KeyValueModel*> models_;
};

} // namespace models
} // namespace api
