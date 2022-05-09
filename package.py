# pylint: disable=invalid-name
name = "katanausd"

version = "19.11_fn8-patched"

authors = ["Pixar", "Foundry"]

description = """
    A USD (Universal Scene Description) plugin for Katana.

    The KatanaUsdPlugins were originally authored by Pixar and this repository
    was originally based on the 19.11 version of the USD library.
    """

requires = ["platform-linux", "katana"]

variants = [
    #["katana-4.0"],
    # FIXME: not building because external/FnBoost and external/FnTBB renamed... grrr
    ["devtoolset-6", "katana-4.5"],
]

private_build_requires = ["cmake-3.12+"]

uuid = "23bc9b7a-fb47-47d2-b674-aef259b77b78"


def commands(env):
    """Commands that will be ran at the execution of rez-env."""

    env.KATANA_USD_LOCATION = "{root}"

    env.KATANA_RESOURCES.append("{root}/plugin")

    env.LD_LIBRARY_PATH.append("{root}/lib")
    env.LD_LIBRARY_PATH.append("{root}/lib/usd/libs")
    env.LD_LIBRARY_PATH.append("{root}/plugin/Libs")

    env.PYTHONPATH.append("{root}/lib/python/fnpxr")

    env.USD_KATANA_ALLOW_CUSTOM_MATERIAL_SCOPES = True  # Used by patch 0001
