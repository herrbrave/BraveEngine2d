#pragma once

#include "Asset.h"
#include "System.h"

class AssetSystem;
typedef std::shared_ptr<AssetSystem> AssetSystemPtr;
typedef std::weak_ptr<AssetSystem> WeakAssetSystemPtr;


class AssetSystem : public System {
public:
	AssetSystem();

	void registerAsset(AssetPtr asset);

	void deregisterAsset(const string& assetTag);

	AssetPtr getAsset(const string& assetTag);

	bool contains(const string& assetTag);

	void clear() override;

	class DefaultAssetVendor : public AssetVendor {
	public:
		DefaultAssetVendor(AssetSystemPtr assetSystem) {
			this->assetSystem = assetSystem;
		}
		AssetPtr getAsset(const string& tag) override;
	private:
		AssetSystemPtr assetSystem;
	};

private:
	unordered_map<string, AssetPtr> assets;
};