#include "pxr/pxr.h"
#include "pxr/usd/usdLux/light.h"

#include "usdKatana/utils.h"

#include "pxrUsdInArnold/declareCoreOps.h"


PXR_NAMESPACE_USING_DIRECTIVE


PXRUSDKATANA_USDIN_PLUGIN_DEFINE(
        PxrUsdInArnold_LocationDecorator, privateData, opArgs, interface)
{
    if (!privateData.hasOutputTarget("arnold"))
    {
        return;
    }

    const UsdPrim& prim = privateData.GetUsdPrim();

    static const std::unordered_map<std::string, std::string> arnoldStatementsMap = {
        {"primvars:arnold:transform_type", "arnoldStatements.transform_type"},
        {"primvars:arnold:invert_normals", "arnoldStatements.invert_normals"},
        {"primvars:arnold:smoothing", "arnoldStatements.smoothing"},
        {"primvars:arnold:subdiv_iterations", "arnoldStatements.iterations"},
        {"primvars:arnold:subdiv_smooth_derivs", "arnoldStatements.subdiv_smooth_derivs"},
        {"primvars:arnold:subdiv_frustum_ignore", "arnoldStatements.subdiv_frustum_ignore"},
        {"primvars:arnold:subdiv_adaptive_error", "arnoldStatements.subdiv_adaptive_error"},
        {"primvars:arnold:subdiv_adaptive_metric", "arnoldStatements.subdiv_adaptive_metric"},
        {"primvars:arnold:subdiv_adaptive_space", "arnoldStatements.subdiv_adaptive_space"},
        {"primvars:arnold:disp_padding", "arnoldStatements.disp_padding"},
        {"primvars:arnold:disp_height", "arnoldStatements.disp_height"},
        {"primvars:arnold:zero_value", "arnoldStatements.zero_value"},
        {"primvars:arnold:disp_autobump", "arnoldStatements.disp_autobump"},
        {"primvars:arnold:opaque", "arnoldStatements.opaque"},
        {"primvars:arnold:matte", "arnoldStatements.matte"},
        {"primvars:arnold:visibility:camera", "arnoldStatements.visibility.AI_RAY_CAMERA"},
        {"primvars:arnold:visibility:shadow", "arnoldStatements.visibility.AI_RAY_SHADOW"},
        {"primvars:arnold:visibility:diffuse_transmit", "arnoldStatements.visibility.AI_RAY_DIFFUSE_TRANSMIT"},
        {"primvars:arnold:visibility:specular_transmit", "arnoldStatements.visibility.AI_RAY_SPECULAR_TRANSMIT"},
        {"primvars:arnold:visibility:volume", "arnoldStatements.visibility.AI_RAY_VOLUME"},
        {"primvars:arnold:visibility:diffuse_reflect", "arnoldStatements.visibility.AI_RAY_DIFFUSE_REFLECT"},
        {"primvars:arnold:visibility:specular_reflect", "arnoldStatements.visibility.AI_RAY_SPECULAR_REFLECT"},
        {"primvars:arnold:sidedness:camera", "arnoldStatements.sidedness.AI_RAY_CAMERA"},
        {"primvars:arnold:sidedness:shadow", "arnoldStatements.sidedness.AI_RAY_SHADOW"},
        {"primvars:arnold:sidedness:diffuse_transmit", "arnoldStatements.sidedness.AI_RAY_DIFFUSE_TRANSMIT"},
        {"primvars:arnold:sidedness:specular_transmit", "arnoldStatements.sidedness.AI_RAY_SPECULAR_TRANSMIT"},
        {"primvars:arnold:sidedness:volume", "arnoldStatements.sidedness.AI_RAY_VOLUME"},
        {"primvars:arnold:sidedness:diffuse_reflect", "arnoldStatements.sidedness.AI_RAY_DIFFUSE_REFLECT"},
        {"primvars:arnold:sidedness:specular_reflect", "arnoldStatements.sidedness.AI_RAY_SPECULAR_REFLECT"},
		{"primvars:arnold:samples", "arnoldLightStatements.samples"},
		{"primvars:arnold:volume_samples", "arnoldLightStatements.volume_samples"},
		{"primvars:arnold:cast_shadows", "arnoldLightStatements.cast_shadows"},
		{"primvars:arnold:cast_volumetric_shadows", "arnoldLightStatements.cast_volumetric_shadows"},
		{"primvars:arnold:shadow_density", "arnoldLightStatements.shadow_density"},
		{"primvars:arnold:shadow_color", "arnoldLightStatements.shadow_color"},
		{"primvars:arnold:camera", "arnoldLightStatements.camera"},
		{"primvars:arnold:transmission", "arnoldLightStatements.transmission"},
		{"primvars:arnold:diffuse", "arnoldLightStatements.diffuse"},
		{"primvars:arnold:specular", "arnoldLightStatements.specular"},
		{"primvars:arnold:sss", "arnoldLightStatements.sss"},
		{"primvars:arnold:indirect", "arnoldLightStatements.indirect"},
		{"primvars:arnold:volume", "arnoldLightStatements.volume"},
		{"primvars:arnold:normalize", "arnoldLightStatements.normalize"},
		{"primvars:arnold:max_bounces", "arnoldLightStatements.max_bounces"},
		{"primvars:arnold:aov", "arnoldLightStatements.lightGroup"},
		/*
		{"primvars:arnold:angle", "material.arnoldLightShader.angle"},
		{"primvars:arnold:portal", "material.arnoldLightShader.portal"},
		{"primvars:arnold:portal_mode", "material.arnoldLightShader.portal_mode"},
		{"primvars:arnold:resolution", "material.arnoldLightShader.resolution"},
		{"primvars:arnold:roundness", "material.arnoldLightShader.angle"},
		{"primvars:arnold:soft_edge", "material.arnoldLightShader.soft_edge"},
		{"primvars:arnold:spread", "material.arnoldLightShader.spread"},
		*/
    };

    if(prim.IsA<UsdLuxLight>()){

    	static const std::unordered_map<std::string, std::string> arnoldLightMap = {
    		{"CylinderLight", "cylinder_light"},
    		{"DiskLight", "spot_light"},
			{"DistantLight", "distant_light"},
    		{"GeometryLight", "mesh_light"},
    		{"SphereLight", "point_light"},
			{"RectLight", "quad_light"},
			{"DomeLight", "skydome_light"},
    	};

		std::unordered_map<std::string, std::string>::const_iterator arnoldLight =
				arnoldLightMap.find(prim.GetTypeName());
    	if(arnoldLight != arnoldLightMap.end()){
			interface.setAttr("material.arnoldLightShader",
					FnKat::StringAttribute(arnoldLight->second));
    	}
    }

    // TODO: Should we check if the location type is a polymesh or subdmesh ?
    UsdAttribute usdAttr;
    for (auto& it: arnoldStatementsMap) {
        usdAttr = prim.GetAttribute(TfToken(it.first));

        if (not usdAttr) {
            continue;
        }

        VtValue vtValue;
        if (not usdAttr.Get(&vtValue)){
            continue;
        }

        FnKat::Attribute katAttr = PxrUsdKatanaUtils::ConvertVtValueToKatAttr(vtValue);

        interface.setAttr(it.second, katAttr);
    }

    // Special case for the following two attributes as the values exported from
    // Solaris are integers but Katana requires strings

    if (UsdAttribute sdType = prim.GetAttribute(TfToken("primvars:arnold:subdiv_type"))) {
        VtValue sdTypeVal;
        sdType.Get(&sdTypeVal);
        if (sdTypeVal.IsHolding<std::string>()) {
            interface.setAttr("arnoldStatements.subdiv_type", FnKat::StringAttribute(sdTypeVal.Get<std::string>()));
        } else if (sdTypeVal.IsHolding<int>()) {
            if (sdTypeVal == 0)
                interface.setAttr("arnoldStatements.subdiv_type", FnKat::StringAttribute("none"));
            else if (sdTypeVal == 1)
                interface.setAttr("arnoldStatements.subdiv_type", FnKat::StringAttribute("catclark"));
            else if (sdTypeVal == 2)
                interface.setAttr("arnoldStatements.subdiv_type", FnKat::StringAttribute("linear"));
        }
    }

    if (UsdAttribute sdUVSmooth = prim.GetAttribute(TfToken("primvars:arnold:subdiv_uv_smoothing"))) {
        VtValue sdUVSmoothVal;
        sdUVSmooth.Get(&sdUVSmoothVal);
        if (sdUVSmoothVal.IsHolding<int>()) {
            if (sdUVSmoothVal == 0)
                interface.setAttr("arnoldStatements.subdiv_uv_smoothing", FnKat::StringAttribute("pin_corners"));
            else if (sdUVSmoothVal == 1)
                interface.setAttr("arnoldStatements.subdiv_uv_smoothing", FnKat::StringAttribute("pin_borders"));
            else if (sdUVSmoothVal == 2)
                interface.setAttr("arnoldStatements.subdiv_uv_smoothing", FnKat::StringAttribute("linear"));
            else if (sdUVSmoothVal == 3)
                interface.setAttr("arnoldStatements.subdiv_uv_smoothing", FnKat::StringAttribute("smooth"));
        }
    }
}
