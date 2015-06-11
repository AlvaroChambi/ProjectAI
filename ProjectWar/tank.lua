unit = {
    --Unit id is defined by the engine
    -- id = " "

    --Tiles that the unit can move in one turn
    movement = 4,
    resource = "tank.png",
    --Range of attack in tiles
    attack_range = 1,
    -- relative initial position in the map (row, column)
    position = {
        row = 4,
        column = 8
    },
    --hitpoints (max: 10)
    hp = 10;
    --type of the unit (Soldier, Tank, Anti-tank)
    type = "Tank",
    --Commands available for the unit
    commands = {
        move = true,
        attack = true,
    },
}