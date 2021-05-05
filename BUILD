package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "hydro-carbon",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
    ],
    srcs = ["main.cc"],
    deps = [
        ":game",
        ":screens",
    ],
)

# Basic framework objects

cc_library(
    name = "audio",
    srcs = ["audio.cc"],
    hdrs = ["audio.h"],
)

cc_library(
    name = "graphics",
    srcs = ["graphics.cc"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "input",
    srcs = ["input.cc"],
    hdrs = ["input.h"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cc"],
    hdrs = ["screen.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
    ]
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
        ":screen",
        ":screens",
        ":text",
    ],
)

# Graphical objects

cc_library(
    name = "animated_sprite",
    srcs = ["animated_sprite.cc"],
    hdrs = ["animated_sprite.h"],
    deps = [":sprite"],
)

cc_library(
    name = "backdrop",
    srcs = ["backdrop.cc"],
    hdrs = ["backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "floating_text",
    srcs = ["floating_text.cc"],
    hdrs = ["floating_text.h"],
    deps = [":text"],
)

cc_library(
    name = "multi_sprite",
    srcs = ["multi_sprite.cc"],
    hdrs = ["multi_sprite.h"],
    deps = [":sprite"],
)

cc_library(
    name = "particles",
    srcs = [
        "ghost.cc",
        "particle.cc",
        "smoke.cc",
    ],
    hdrs = [
        "ghost.h",
        "particle.h",
        "smoke.h",
    ],
    deps = [
        ":animated_sprite",
        ":graphics",
        ":sprite",
    ],
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    deps = [":graphics"],
)

cc_library(
    name = "text",
    srcs = ["text.cc"],
    hdrs = ["text.h"],
    deps = [":graphics"],
)

cc_library(
    name = "screens",
    srcs = [
        "game_over_screen.cc",
        "game_screen.cc",
        "screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "game_over_screen.h",
        "game_screen.h",
        "screen.h",
        "title_screen.h",
    ],
    deps = [
        ":backdrop",
        ":map",
        ":message",
        ":multi_sprite",
        ":particles",
        ":screen",
        ":sprite",
        ":text",
        ":water_objects",
    ],
)

cc_library(
    name = "map",
    srcs = ["map.cc"],
    hdrs = ["map.h"],
    deps = [
        ":animated_sprite",
    ]
)

cc_library(
    name = "message",
    srcs = ["message.cc"],
    hdrs = ["message.h"],
    deps = [
        ":animated_sprite",
        ":sprite",
        ":text",
    ]
)

cc_library(
    name = "water_objects",
    srcs = [
        "barrel.cc",
        "boat.cc",
        "fish.cc",
        "police.cc",
        "tanker.cc",
        "water_obj.cc",
        "whale.cc",
    ],
    hdrs = [
        "barrel.h",
        "boat.h",
        "fish.h",
        "police.h",
        "tanker.h",
        "water_obj.h",
        "whale.h",
    ],
    deps = [
        ":audio",
        ":map",
        ":particles",
        ":sprite",
    ],
)

