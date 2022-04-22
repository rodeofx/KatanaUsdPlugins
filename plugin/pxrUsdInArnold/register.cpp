#include "pxr/pxr.h"

#include "pxrUsdInArnold/declareCoreOps.h"

#include "usdKatana/bootstrap.h"
#include "vtKatana/bootstrap.h"

PXR_NAMESPACE_USING_DIRECTIVE


DEFINE_GEOLIBOP_PLUGIN(PxrUsdInArnold_LocationDecorator);

void registerPlugins()
{
    USD_OP_REGISTER_PLUGIN(PxrUsdInArnold_LocationDecorator,
            "PxrUsdInArnold_LocationDecorator",
            0,
            1);

    PxrUsdKatanaUsdInPluginRegistry::RegisterLocationDecoratorOp(
            "PxrUsdInArnold_LocationDecorator");

    PxrUsdKatanaBootstrap();
    PxrVtKatanaBootstrap();
}
