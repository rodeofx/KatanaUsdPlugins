#include "pxrUsdInRdo/declareCoreOps.h"

#include "pxr/pxr.h"

#include "pxr/usd/usdVol/openVDBAsset.h"

#include "usdKatana/bootstrap.h"
#include "vtKatana/bootstrap.h"

PXR_NAMESPACE_USING_DIRECTIVE


DEFINE_GEOLIBOP_PLUGIN(PxrUsdInRdo_OpenVDBAssetOp);

void registerPlugins()
{
    USD_OP_REGISTER_PLUGIN(PxrUsdInRdo_OpenVDBAssetOp,
            "PxrUsdInRdo_OpenVDBAssetOp",
            0,
            1);

    PxrUsdKatanaUsdInPluginRegistry::RegisterUsdType<UsdVolOpenVDBAsset>(
            "PxrUsdInRdo_OpenVDBAssetOp");

    PxrUsdKatanaBootstrap();
    PxrVtKatanaBootstrap();
}
