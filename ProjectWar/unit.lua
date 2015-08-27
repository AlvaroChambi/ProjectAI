unit = {
    --Unit id is defined by the engine
    -- id = " "

    --Tiles that the unit can move in one turn
    movement = 3,
    resource = "soldier_red.png",
    --Range of attack in tiles
    attack_range = 1,
    --hitpoints (max: 10)
    hp = 10;
    --type of the unit (Soldier, Tank, Anti-tank)
    type = "soldier",
    --Commands available for the unit
    commands = {
        move = true,
        attack = true,
        capture = true,
    },
}