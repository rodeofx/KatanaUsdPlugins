#include "pxrUsdInRdo/declareCoreOps.h"

#include "pxr/pxr.h"

#include "usdKatana/attrMap.h"
#include "usdKatana/readPrim.h"
#include "usdKatana/readXformable.h"
#include "usdKatana/utils.h"

#include "pxr/usd/usdVol/volume.h"

PXR_NAMESPACE_USING_DIRECTIVE

PXRUSDKATANA_USDIN_PLUGIN_DEFINE(
        PxrUsdInRdo_VolumeOp, privateData, opArgs, interface)
{
    PxrUsdKatanaAttrMap attrs;

    const UsdPrim& prim = privateData.GetUsdPrim();
    PxrUsdKatanaReadPrim(prim, privateData, attrs);
    PxrUsdKatanaReadXformable(UsdGeomXformable(prim), privateData, attrs);

    attrs.toInterface(interface);
}
