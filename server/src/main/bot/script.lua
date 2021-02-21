map = {}
player = {killing = 0, moving = 0, rotating = 0, inited = false }
position = {x=0, y=0, direction = 0 }
enemy = {id = 0, health = -1}
pace = 1
differenceAllowed = 5

function init(packetsReceived, paceReceived, differenceAllowedReceived, rotationSpeedReceived)
    packets = packetsReceived
    pace = paceReceived
    differenceAllowed = differenceAllowedReceived
    rotationSpeed = rotationSpeedReceived
end

function resetPlayer()
    player.killing = 0
    player.moving = 0
    player.rotating = 0
    enemy.health = -1
    enemy.id = 0
    path = nil
end

function loadMap(x, y, value)
    if map[x] == nil then map[x] = {} end --???

    if value ~= 0 and value ~= 1 then
        value = 1
    end
    map[x][y] = value
    --print(x,y,value)
end

function updatePlayer(currentPlayer, goal)
    player.inited = true
    for key, value in pairs(currentPlayer) do
        player[key] = value
    end
    --if player.moving == 1 and prev_node ~=nil and (prev_node.x ~= player.posX or prev_node.y ~= player.posY) then
    --player.moving = 0
    --end
    --print(player.angle)
    if player.killing == 1 then
        prev_node = nil
    end
    for key, value in pairs(goal) do
        enemy[key] = value
    end
end

function round(num, numDecimalPlaces)
    local mult = 10^(numDecimalPlaces or 0)
    return math.floor(num * mult + 0.5) / mult
end

function randomize(first, second)
    math.randomseed(os.clock()*100000000000)
    return math.random(first, second)
end

function move()
    player.moving = 1
    --return position, packets.move
    return position, packets.move
end

function move_up_left()
    position.x = player.posX - 1 * math.sqrt(2)/2 * pace
    position.y = player.posY - 1 * math.sqrt(2)/2 * pace
    --print("UP_LEFT 2")
    --position.direction = 2
    --print("UP RIGHT 8")
    position.direction = 8
end
function move_up()
    position.x = player.posX
    position.y = player.posY - 1 * pace
    --print("UP 1")
    --position.direction = 1
    --print("LEFT 3")
    --position.direction = 3
    --print("RIGHT 7")
    position.direction = 7
end
function move_up_right()
    position.x = player.posX + 1 * math.sqrt(2)/2 * pace
    position.y = player.posY - 1 * math.sqrt(2)/2 * pace
    --print("UP RIGHT 8")
    --position.direction = 8
    --print("DOWN_LEFT 4")
    --position.direction = 4
    --print("DOWN RIGHT 6")
    position.direction = 6
end
function move_right()
    position.x = player.posX + 1 * pace
    position.y = player.posY
    --print("RIGHT 7")
    --position.direction = 7
    --print("DOWN 5")
    position.direction = 5
end
function move_down_right()
    position.x = player.posX + 1 * math.sqrt(2)/2 * pace
    position.y = player.posY + 1 * math.sqrt(2)/2 * pace
    --print("DOWN RIGHT 6")
    --position.direction = 6
    --print("DOWN_LEFT 4")
    position.direction = 4
end
function move_down()
    position.x = player.posX
    position.y = player.posY + 1 * pace
    --print("DOWN 5")
    --position.direction = 5
    --print("RIGHT 7")
    --position.direction = 7
    --print("LEFT 3")
    position.direction = 3
end
function move_down_left()
    position.x = player.posX - 1 * math.sqrt(2)/2 * pace
    position.y = player.posY + 1 * math.sqrt(2)/2 * pace
    --print("DOWN_LEFT 4")
    --position.direction = 4
    --print("UP RIGHT 8")
    --position.direction = 8
    --print("UP_LEFT 2")
    position.direction = 2

end
function move_left()
    position.x = player.posX - 1 * pace
    position.y = player.posY
    --print("LEFT 3")
    --position.direction = 3
    --print("UP 1")
    position.direction = 1
end

function is_position_updated()
    if prev_node == nil then
        return true
    end
    --[[    local x_info = math.abs(prev_node.x - player.posX)
                / prev_node.x * 100
        local y_info = math.abs(prev_node.y - player.posY)
                / prev_node.y * 100]]
    local x_info = math.abs(prev_node.x - player.posX)
    local y_info = math.abs(prev_node.y - player.posY)

    local is_ok = ( (x_info <= differenceAllowed)
            and (y_info <= differenceAllowed) )
    return ( is_ok )
end

function updatePath(playerX, playerY, playerID)
    if not is_position_updated() then
        find_best_path(playerX, playerY, playerID)
        if path then
            --player.moving = 1
            player.rotating = 1
            prev_node = nil
            enemy.id = playerID
        else
            return random_movement()
        end


        --return execute(playerX, playerY, playerID)
    end

    if path then
        for node in path:nodes() do
            if (prev_node == nil)
                    or (prev_node.x == node.x
                    and prev_node.y == node.y) then
                prev_node = node
            else
                if prev_node.x == (node.x+1)
                        and prev_node.y == (node.y+1) then
                    move_up_left()
                elseif prev_node.x == node.x
                        and prev_node.y == (node.y+1) then
                    move_up()
                elseif prev_node.x == (node.x-1)
                        and prev_node.y == (node.y+1) then
                    move_up_right()
                elseif prev_node.x == (node.x-1)
                        and prev_node.y == node.y then
                    move_right()
                elseif prev_node.x == (node.x-1)
                        and prev_node.y == (node.y-1) then
                    move_down_right()
                elseif prev_node.x == node.x
                        and prev_node.y == (node.y-1) then
                    move_down()
                elseif prev_node.x == (node.x+1)
                        and prev_node.y == (node.y-1) then
                    move_down_left()
                elseif prev_node.x == (node.x+1)
                        and prev_node.y == node.y then
                    move_left()
                else
                    io.write("ERROR en updatePath")
                end
                --[]io.write("PrevNode("..prev_node.x.." "..prev_node.y..")".."Node("..node.x.." "..node.y..")".."\n")
                prev_node = node
                break
            end
        end
        table.remove(path, 1) --todo low efficience ?...
        --for node, count in path:nodes() do
        --print(('Step: %d - x: %d - y: %d'):format(count, node.x, node.y))
        --end
        return move()
    end
end

function kill()
    player.killing = 1
    return randomize(1,10), packets.damage
end

function setKilling()
    player.killing = 1
end

function resetMoving()
    player.moving = 0
end

function canMove()
    if map[round(position.x, 0)] == nil or
            map[round(position.x, 0)]
            [round(position.y, 0)] == nil then
        return false
    end

    if map[round(position.x, 0)]
    [round(position.y, 0)] == 1 then
        return false
    end
    if map[round(position.x, 0)]
    [round(position.y, 0)] == 0 then
        return true
    end
    return false
end

function random_movement()

    return position
    --remove above
    --[[
    local rand = randomize(1,8)

    if rand == 1 then
        move_up_left()
    elseif rand == 2 then
        move_up()
    elseif rand == 3 then
        move_up_right()
    elseif rand == 4 then
        move_right()
    elseif rand == 5 then
        move_down_right()
    elseif rand == 6 then
        move_down()
    elseif rand == 7 then
        move_down_left()
    elseif rand == 8 then
        move_left()
    end

    if canMove() then
        return position, packets.move--move()
    else
        return random_movement()
    end
]]
end
function find_best_path(playerX, playerY, playerID)
    local Grid = require ('jumper.grid')
    local Pathfinder = require ('jumper.pathfinder')
    local grid = Grid(map)
    local myFinder = Pathfinder(grid, 'ASTAR', 0):
    setHeuristic('DIAGONAL'):
    setMode('DIAGONAL')

    path = myFinder:getPath(round(player.posX,0),
        round(player.posY,0),
        round(playerX, 0),
        round(playerY,0))
    --return path
end
function execute(playerX, playerY, playerID)
    --print("ATACAR A: ")
    --print(playerID)
    --print(" ")
    find_best_path(playerX, playerY, playerID)
    if path then
        --player.moving = 1
        player.rotating = 1
        prev_node = nil
        enemy.id = playerID
    else
        return random_movement()
    end
    --if player.moving == 1 then
      --  return updatePath(playerX, playerY, playerID)
    --end
end

function shouldRotate()
    local difference = enemy.angleToGoal - player.angle
    if  math.abs(difference) < 0.5 then
        return false
    else
        return true
    end
end


function rotate(--[[angleToGoal]])
    --[[
    // Rotating directions:
    #define INVALID_ROTATION 0
    #define RIGHT_ROTATION 1
    #define LEFT_ROTATION 2
    ]]
    local difference = enemy.angleToGoal - player.angle
    if shouldRotate(enemy.angleToGoal) then
        if player.angle + rotationSpeed > player.angle - rotationSpeed then
            print("A")
            return 2, packets.rotate --change 1
        else
            print("B")
            return 1, packets.rotate --change 2
        end
    else
        player.rotating = 0
        player.moving = 1
        return 0, 25 --No hago nada. Se pierde una iteración . TODO CHECK
    end

    --[[
    //double angle_to_goal = map.get_player(id_at_players).get_position().
//  angle_to(player_goal->get_position());
    //double own_angle = map.get_player(id_at_players).get_angle();
    //printf("|%f||%f|", angle_to_goal, own_angle);
    //printf("|%f|", abs(angle_to_goal - own_angle));
]]
end

function decision()
    if(not player.inited) then
        --[]io.write("jugador no inicializado")
        return 0
    end
    if enemy.health == 0 or
            (player.moving == 0 and player.killing == 0 and player.rotating == 0) then
        --io.write("---"..enemy.health.." "..player.moving.." "..player.killing.."---")
        resetPlayer()
        return 1
    end
    if shouldRotate() then
        player.rotate = 1
        --print("TENES QUE ROTAR CHE")
        return 4
    else
        --print("no rotes")
    end
    if player.killing == 1 then
        return 2
    end
    if player.moving == 1 then
        return 3
    end
    if player.rotating == 1 then
        return 4
    end
    return -1
end
