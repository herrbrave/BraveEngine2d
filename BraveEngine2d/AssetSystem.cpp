#include "AssetSystem.h"

AssetSystem::AssetSystem() : System(SystemType::ASSET) {
}

void AssetSystem::registerAsset(AssetPtr asset) {
	this->assets.emplace(asset->tag, asset);
}

void AssetSystem::deregisterAsset(const string& assetTag) {
	this->assets.erase(assets.find(assetTag));
}

AssetPtr AssetSystem::getAsset(const string& assetTag) {
	return this->assets.at(assetTag);
}

bool AssetSystem::contains(const string& assetTag) {
	return (this->assets.find(assetTag) != assets.end());
}

AssetPtr AssetSystem::DefaultAssetVendor::getAsset(const string& tag) {
	return this->assetSystem->getAsset(tag);
}

void AssetSystem::clear() {
	this->assets.clear();
}