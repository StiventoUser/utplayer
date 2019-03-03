#pragma once

#include <QAbstractItemModel>
#include <QDebug>
#include <QSet>
namespace api
{
namespace models
{

class KeyValueModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	using StringMap = QVector<QPair<QString, QVariant>>;
	using ModelType = QVector<StringMap>;

public:
	KeyValueModel(QObject* parent = nullptr);

public:
	ModelType GetData() const;
	void SetData(const ModelType& data);

	int columnCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent) const override;
	QModelIndex parent(const QModelIndex& child) const override;
	QHash<int, QByteArray> roleNames() const override;
	int rowCount(const QModelIndex& parent = {}) const override;

public slots:
	QVariantMap getItemMapByIndex(const int index) const;

private:
	ModelType data_;
	QSet<QString> keys_;
};

} // namespace models
} // namespace api
