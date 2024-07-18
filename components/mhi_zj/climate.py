import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate_ir
from esphome.const import CONF_ID

CODEOWNERS = ["@mSapik"]
AUTO_LOAD = ["climate_ir"]

mhi_ns = cg.esphome_ns.namespace("mhi_zj")
MhiClimate = mhi_ns.class_("MhiClimate", climate_ir.ClimateIR)

CONF_HORIZONTAL_DEFAULT = "horizontal_default"
HorizontalDirections = mhi_ns.enum("HorizontalDirections")
HORIZONTAL_DIRECTIONS = {
    "swing": HorizontalDirections.MHI_HS_SWING,
    "left": HorizontalDirections.MHI_HS_LEFT,
    "middle-left": HorizontalDirections.MHI_HS_MLEFT,
    "middle": HorizontalDirections.MHI_HS_MIDDLE,
    "middle-right": HorizontalDirections.MHI_HS_MRIGHT,
    "right": HorizontalDirections.MHI_HS_RIGHT,
    "left-right": HorizontalDirections.MHI_HS_LEFTRIGHT,
    "right-left": HorizontalDirections.MHI_HS_RIGHTLEFT,
    "3D-Auto": HorizontalDirections.MHI_HS_3DAUTO,
}

CONF_VERTICAL_DEFAULT = "vertical_default"
VerticalDirections = mhi_ns.enum("VerticalDirections")
VERTICAL_DIRECTIONS = {
    "swing": VerticalDirections.MHI_VS_SWING,
    "up": VerticalDirections.MHI_VS_UP,
    "middle-up": VerticalDirections.MHI_VS_MUP,
    "middle": VerticalDirections.MHI_VS_MIDDLE,
    "middle-down": VerticalDirections.MHI_VS_MDOWN,
    "down": VerticalDirections.MHI_VS_DOWN,
}


CONFIG_SCHEMA = climate_ir.CLIMATE_IR_WITH_RECEIVER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(MhiClimate),
        cv.Optional(CONF_HORIZONTAL_DEFAULT, default="middle"): cv.enum(
            HORIZONTAL_DIRECTIONS
        ),
        cv.Optional(CONF_VERTICAL_DEFAULT, default="middle"): cv.enum(
            VERTICAL_DIRECTIONS
        ),        
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await climate_ir.register_climate_ir(var, config)

    cg.add(var.set_horizontal_default(config[CONF_HORIZONTAL_DEFAULT]))
    cg.add(var.set_vertical_default(config[CONF_VERTICAL_DEFAULT]))
