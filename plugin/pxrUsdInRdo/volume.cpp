#include "pxrUsdInRdo/declareCoreOps.h"

#include "pxr/pxr.h"

#include "usdKatana/attrMap.h"
#include "usdKatana/readPrim.h"
#include "usdKatana/utils.h"

#include "pxr/usd/usdVol/volume.h"

PXR_NAMESPACE_USING_DIRECTIVE

PXRUSDKATANA_USDIN_PLUGIN_DEFINE(
        PxrUsdInRdo_VolumeOp, privateData, opArgs, interface)
{
    PxrUsdKatanaAttrMap attrs;

    PxrUsdKatanaReadPrim(privateData.GetUsdPrim(), privateData, attrs);

    attrs.toInterface(interface);
}
