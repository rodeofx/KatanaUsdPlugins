# pylint: disable=invalid-name
name = "KatanaUsdPlugins"

version = "19.11_fn7"

authors = ["Pixar", "Foundry"]

description = """
    A USD (Universal Scene Description) plugin for Katana.

    The KatanaUsdPlugins were originally authored by Pixar and this repository
    was originally based on the 19.11 version of the USD library.
    """

requires = ["platform-linux", "katana"]

variants = [
    ["katana-4.0"],
    # FIXME: not building because external/FnBoost and external/FnTBB renamed... grrr
    # ["katana-4.5"],
]

private_build_requires = ["cmake-3.12+"]

uuid = "98fcc517-197a-4c89-a4fc-03388b83fb8d"


def commands(env):
    """Commands that will be ran at the execution of rez-env."""

    env.KATANA_USD_LOCATION = "{root}"

    env.KATANA_RESOURCES.append("{root}/plugin")

    env.LD_LIBRARY_PATH.append("{root}/lib")
    env.LD_LIBRARY_PATH.append("{root}/lib/usd/libs")
    env.LD_LIBRARY_PATH.append("{root}/plugin/Libs")

    env.PYTHONPATH.append("{root}/lib/python/fnpxr")

    env.USD_KATANA_ALLOW_CUSTOM_MATERIAL_SCOPES = True  # Used by patch 0001
