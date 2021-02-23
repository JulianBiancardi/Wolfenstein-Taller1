map = {}
player = {killing = 0, moving = 0, rotating = 0, rotation_orientation = 0, inited = false}
enemy = {id = 0, health = -1 }

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
    path = nil
end

function loadMap(x, y, value)
    if map[y+1] == nil then
        map[y+1] = {}
    end
    if value == 0 then
        map[y+1][x+1] = 0
    else
        map[y+1][x+1] = 1
    end
end

function updatePlayer(currentPlayer, goal)
    player.inited = true
    for key, value in pairs(currentPlayer) do
        player[key] = value
    end
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
    return packets.move
end
function isEnemyInPath(node)
    local x_info = math.abs(node.x - 1 + 0.5 - enemy.posX)
    local y_info = math.abs(node.y - 1 + 0.5 - enemy.posY)
    local is_ok = ( (x_info <= differenceAllowed)
            and (y_info <= differenceAllowed) )
    return ( is_ok )
end

function isDistanceLessThanEpsilon(node)
    if node == nil then
        return false
    end
    local x_info = math.abs(node.x - 1 + 0.5 - player.posX)
    local y_info = math.abs(node.y - 1 + 0.5 - player.posY)
    local is_ok = ( (x_info <= 0.15)
            and (y_info <= 0.15) )
    return ( is_ok )
end
function updatePath(playerX, playerY, playerID)
    if path then
        local node = path[1]
        if node == nil then
            resetMoving()
            return 0
        end
        local next_pos_angle = angleTo(player.posX, player.posY, node.x - 1 + 0.5, node.y - 1 + 0.5)
        if shouldRotate(next_pos_angle, player.angle) then
            player.moving = 0
            player.rotating = 1
            return 0
        end
        if not isDistanceLessThanEpsilon(node) then
            return move()
        end
        table.remove(path, 1)
        if not isEnemyInPath(path[#path]) then
            resetPlayer()
            return 0
        end
        if player.rotating == 0 then
            return move()
        else
            return 0
        end
    else
        resetMoving()
        return 0
    end
end
function kill()
    player.killing = 1
    return randomize(1,2), packets.damage
end

function setKilling()
    player.killing = 1
end

function resetMoving()
    player.moving = 0
end

function find_best_path(playerX, playerY, playerID)
    local Grid = require ('jumper.grid')
    local Pathfinder = require ('jumper.pathfinder')
    local grid = Grid(map)
    local myFinder = Pathfinder(grid, 'ASTAR', 0):
    setHeuristic('DIAGONAL'):
    setMode('ORTHOGONAL')    --setMode('DIAGONAL')
    path = myFinder:getPath(math.floor(player.posX)+1,
                math.floor(player.posY)+1,
                math.floor(playerX)+1,
                math.floor(playerY)+1)
    table.remove(path, 1) --Remuevo la posición actual
end
function execute(playerX, playerY, playerID)
    find_best_path(playerX, playerY, playerID)
    if path then
        player.moving = 1
        prev_node = nil
    else
        return 0
    end
    return 0
end

function angleTo(firstX, firstY, secondX, secondY)
    local angle = math.atan2(firstY - secondY, secondX - firstX)
    if angle >= 2 * math.pi then
        repeat
            angle = angle - 2 * math.pi
        until angle <= 2 * math.pi
    end
    if angle < 0 then
        repeat
            angle = angle + 2 * math.pi
        until angle >= 0
    end
    return angle
end

function shouldRotate(firstAngle, secondAngle)
    local difference = firstAngle - secondAngle
    if math.abs(difference) < 0.25 then --0.5 ideal? 0.25 funca bien
        return false
    else
        return true
    end
end
function rotate()
    local next_pos_angle
    local node_local
    if path then
        local node = path[1]
        next_pos_angle = angleTo(player.posX, player.posY, node.x - 1 + 0.5, node.y - 1 + 0.5)
        node_local = node
    end
    if shouldRotate(next_pos_angle, player.angle) then
        local add = player.angle + rotationSpeed
        local substract = player.angle - rotationSpeed
        local next_difference_add = next_pos_angle - add
        local next_difference_subtract = next_pos_angle - substract
        if player.rotation_orientation ~= 0 then
            return player.rotation_orientation, packets.rotate
        end

        if next_pos_angle - player.angle >= math.pi or next_pos_angle - player.angle < 0 then
            player.rotation_orientation = 1
            return 1, packets.rotate --1 Right Rotation
        else
            player.rotation_orientation = 2
            return 2, packets.rotate --2 Left Rotation
        end
    else
        player.rotation_orientation = 0
        player.rotating = 0
        player.moving = 1
        return 0, 0
    end
end

function decision()
    if(not player.inited) then
        return 0
    end
    if enemy.health == 0 or
            (player.moving == 0 and player.killing == 0 and player.rotating == 0) then
        resetPlayer()
        return 1
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
    return 0
end
