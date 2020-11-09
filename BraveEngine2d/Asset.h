#pragma once

#include<memory>
#include<string>

typedef std::shared_ptr<void> VoidPtr;

class Asset {
public:
	std::string path;
	std::string tag;

	Asset(VoidPtr asset, const std::string& path, const std::string& tag) {
		assetPtr = asset;
		this->path = path;
		this->tag = tag;
	}

	template<class ClassType>
	std::shared_ptr<ClassType> getAsset() {
		std::shared_ptr<void> asset = assetPtr;
		std::shared_ptr<ClassType> converted = static_pointer_cast<ClassType>(asset);
		return converted;
	}

private:
	VoidPtr assetPtr;
};
typedef std::shared_ptr<Asset> AssetPtr;
typedef std::weak_ptr<Asset> WeakAssetPtr;

class AssetVendor {
public:
	virtual AssetPtr getAsset(const std::string& tag) = 0;
};
typedef std::shared_ptr<AssetVendor> AssetVendorPtr;
typedef std::weak_ptr<AssetVendor> WeakAssetVendorPtr;
