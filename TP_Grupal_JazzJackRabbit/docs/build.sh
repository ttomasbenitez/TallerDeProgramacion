#!/bin/sh
plantuml server.plantuml
plantuml server-recv-jump.plantuml
plantuml server-recv-creation.plantuml
plantuml server-recv-list.plantuml
plantuml server-level.plantuml
plantuml server-send-gamestate.plantuml
pandoc server.md -o server.pdf
