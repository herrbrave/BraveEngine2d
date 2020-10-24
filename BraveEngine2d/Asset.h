#pragma once

#include<memory>
#include<string>

class Asset;
typedef std::shared_ptr<Asset> AssetPtr;
typedef std::weak_ptr<Asset> WeakAssetPtr;

class AssetVendor;
typedef std::shared_ptr<AssetVendor> AssetVendorPtr;
typedef std::weak_ptr<AssetVendor> WeakAssetVendorPtr;

typedef std::shared_ptr<void> VoidPtr;

class Asset {
public:
	std::string path;
	std::string tag;

	Asset(VoidPtr asset, const std::string& path, const std::string& tag) {
		assetPtr = asset;
		this->tag = std::move(tag);
	}

	template<class ClassType>
	weak_ptr<ClassType> getAsset() {
		shared_ptr<void> asset = assetPtr;
		shared_ptr<ClassType> converted = static_pointer_cast<ClassType>(asset);
		return weak_ptr<ClassType>(converted);
	}

private:
	VoidPtr assetPtr;
};

class AssetVendor {
public:
	virtual AssetPtr getAsset(const std::string& tag) = 0;
};
