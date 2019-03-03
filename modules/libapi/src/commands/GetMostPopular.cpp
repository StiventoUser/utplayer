#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtQml/QQmlEngine>

#include <cpprest/uri_builder.h>

#include "api/Utils.h"
#include "api/commands/GetMostPopular.h"

#include <QDebug>

namespace api
{
namespace commands
{

GetMostPopular::GetMostPopular(QObject* parent) : Command(parent)
{
}

Command::AccessType GetMostPopular::GetAccessType() const
{
	return AccessType::Public;
}

ApiRequest GetMostPopular::GenerateRequest() const
{
	web::uri_builder builder(_XPLATSTR("https://www.googleapis.com/youtube/v3/videos"));
	builder.append_query(_XPLATSTR("part"), _XPLATSTR("snippet,contentDetails,statistics"));
	builder.append_query(_XPLATSTR("chart"), _XPLATSTR("mostPopular"));
	builder.append_query(_XPLATSTR("maxResults"), utils::ToStringT(itemsPerRequest_));

	if (!nextPageToken_.isEmpty() && !nextPageToken_.isNull())
	{
		builder.append_query(_XPLATSTR("pageToken"), utils::QStringToStringT(nextPageToken_));
	}

	return ApiRequest(builder.to_string());
}

void GetMostPopular::ReadResponse(const ApiResponse& response)
{
	responseData_.clear();

	auto resp = QJsonDocument::fromJson(utils::StringTToQString(response.GetText()).toUtf8());

	nextPageToken_ = resp["nextPageToken"].toString();

	const auto pushKv = [this](auto& map, const auto& key, const auto& value) {
		map.push_back({key, value.toVariant()});
	};

	for (const auto& itemRef : resp["items"].toArray())
	{
		const auto item = itemRef.toObject();
		models::KeyValueModel::StringMap itemMap;

		pushKv(itemMap, "videoId", item["id"]);
		pushKv(itemMap, "publishedAt", item["snippet"]["publishedAt"]);
		pushKv(itemMap, "channelId", item["snippet"]["channelId"]);
		pushKv(itemMap, "videoTitle", item["snippet"]["title"]);
		pushKv(itemMap, "videoDescription", item["snippet"]["description"]);
		pushKv(itemMap, "thumbnailDefaultUrl", item["snippet"]["thumbnails"]["default"]["url"]);
		pushKv(itemMap, "thumbnailDefaultWidth", item["snippet"]["thumbnails"]["default"]["width"]);
		pushKv(
			itemMap, "thumbnailDefaultHeight", item["snippet"]["thumbnails"]["default"]["height"]);
		pushKv(itemMap, "thumbnailMediumUrl", item["snippet"]["thumbnails"]["medium"]["url"]);
		pushKv(itemMap, "thumbnailMediumWidth", item["snippet"]["thumbnails"]["medium"]["width"]);
		pushKv(itemMap, "thumbnailMediumHeight", item["snippet"]["thumbnails"]["medium"]["height"]);
		pushKv(itemMap, "channelTitle", item["snippet"]["channelTitle"]);
		pushKv(itemMap, "videoCategoryId", item["snippet"]["categoryId"]);
		pushKv(itemMap, "liveBroadcastContent", item["snippet"]["liveBroadcastContent"]);
		pushKv(itemMap, "videoDuration", item["contentDetails"]["duration"]);
		pushKv(itemMap, "viewCount", item["statistics"]["viewCount"]);
		pushKv(itemMap, "likeCount", item["statistics"]["likeCount"]);
		pushKv(itemMap, "dislikeCount", item["statistics"]["dislikeCount"]);
		pushKv(itemMap, "commentCount", item["statistics"]["commentCount"]);
		pushKv(itemMap, "embedHtml", item["player"]["embedHtml"]);
		pushKv(itemMap, "embedHeight", item["player"]["embedHeight"]);
		pushKv(itemMap, "embedWidth", item["player"]["embedWidth"]);
		pushKv(itemMap, "json", item["id"]);

		responseData_.push_back(itemMap);

		// pushKv("videoTags", item["id"]);
		// pushKv("", item[""]); contentDetails.regionRestriction.allowed[]
		// pushKv("", item[""]); contentDetails.regionRestriction.blocked[]
		// fileDetails.videoStreams[]
		// fileDetails.audioStreams[]
	}

	emit commandReadResponse();
}

QObject* GetMostPopular::getModel()
{
	// WTF QML?
	// https://stackoverflow.com/questions/37325792/qt5-6-qml-why-are-dynamic-models-destroyed-after-garbage-collection
	auto model = new models::KeyValueModelVectorModel(this);
	QQmlEngine::setObjectOwnership(model, QQmlEngine::CppOwnership);
	return model;
}

QObject* GetMostPopular::getPageModel()
{
	auto model = new models::KeyValueModel(this);
	model->SetData(responseData_);

	return model;
}

void GetMostPopular::resetPaging()
{
	nextPageToken_.clear();
}

} // namespace commands
} // namespace api
