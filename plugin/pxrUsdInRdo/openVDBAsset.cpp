#include "pxrUsdInRdo/declareCoreOps.h"

#include "pxr/pxr.h"

#include "usdKatana/attrMap.h"
#include "usdKatana/readMesh.h"
#include "usdKatana/utils.h"

#include "pxr/usd/usdVol/openVDBAsset.h"

PXR_NAMESPACE_USING_DIRECTIVE

PXRUSDKATANA_USDIN_PLUGIN_DEFINE(
        PxrUsdInRdo_OpenVDBAssetOp, privateData, opArgs, interface)
{
    PxrUsdKatanaAttrMap attrs;

    // Set Op attributes
    attrs.set("type", FnKat::StringAttribute("volume"));
    attrs.set("geometry.type", FnKat::StringAttribute("volumeplugin"));
    attrs.set("geometry.step_size", FnAttribute::FloatAttribute(0.0f));
    attrs.set("rendererProcedural.node", FnKat::StringAttribute("volume"));

    // Get the USD data
    const UsdTimeCode time(privateData.GetCurrentTime());
    const UsdVolOpenVDBAsset openVDBAsset(privateData.GetUsdPrim());

    // Get the filename
    SdfAssetPath filePath;
    openVDBAsset.GetFilePathAttr().Get(&filePath, time);

    // Get the name of the field
    TfToken fieldName;
    openVDBAsset.GetFieldNameAttr().Get(&fieldName, time);

    attrs.set("rendererProcedural.args.filename",
            FnKat::StringAttribute(filePath.GetResolvedPath()));
    attrs.set("rendererProcedural.args.grids",
            FnKat::StringAttribute(fieldName.GetString()));

    attrs.toInterface(interface);
}
