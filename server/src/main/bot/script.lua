map = {}
player = {killing = 0, moving = 0, rotating = 0, rotation_orientation = 0, inited = false, working = false }
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
    print(player.posX)
    print(player.posY)
    player.moving = 1
    return 0, packets.move
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
    print("Z")
    if path then
        print("ZZ")
        local node = path[1]
        if node == nil then
            resetMoving()
            return 0,0
        end
        print(player.posX)
        print(player.posY)
        print(node.x - 1 + 0.5)
        print(node.y - 1 + 0.5)
        local next_pos_angle = angleTo(player.posX, player.posY, node.x - 1 + 0.5, node.y - 1 + 0.5)
        print("ZZZZ")
        if shouldRotate(next_pos_angle, player.angle) then
            print("A")
            player.moving = 0
            player.rotating = 1
            return 0, 0
        end
        if not isDistanceLessThanEpsilon(node) then
            print("B")
            return move()
        end
        print("ZZZZZ")
        table.remove(path, 1)
        if not isEnemyInPath(path[#path]) then
            print("C")
            return resetPlayer()
        end
        if player.rotating == 0 then
            print("D")
            return move()
        else
            print("E")
            return 0,0
        end
        --for node, count in path:nodes() do
        --print(('Step: %d - x: %d - y: %d'):format(count, node.x, node.y))
        --end
    else
        print("F")
        resetMoving()
        return 0,0
    end
    print("ZZZZZZZZ")

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

function random_movement()
    return 0
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
    for node, count in path:nodes() do
        print(('Step: %d - x: %d - y: %d'):format(count, node.x - 1, node.y - 1))
    end
end
function execute(playerX, playerY, playerID)
    find_best_path(playerX, playerY, playerID)
    if path then
        player.moving = 1
        prev_node = nil
    else
        return random_movement()
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
    if math.abs(difference) < 0.5 then --0.5 ideal? 0.25 funca bien
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
        print()
        print()
        --print(math.abs(next_difference_add - player.angle))
        --print(math.abs(next_difference_subtract - player.angle))
        --[[
        if (other.angle - me.angle < M_PI) rotate left
            else if (other.angle - me.angle > M_PI) rotate_right
            else: nothing
        ]]
        if next_pos_angle - player.angle < math.pi then
            print("LEFT")
        else
            print("RIGHT")
        end
        --print(math.abs(next_pos_angle - player.angle + rotationSpeed))
        --print(math.abs(next_pos_angle - player.angle - rotationSpeed))
        --print(player.rotation_orientation)
        if player.rotation_orientation ~= 0 then
            return player.rotation_orientation, packets.rotate
        end
        if math.abs(next_difference_add - player.angle) > math.abs(next_difference_subtract - player.angle) then
            player.rotation_orientation = 1
            return 1, packets.rotate --1 Right Rotation
        else
            player.rotation_orientation = 2
            return 2, packets.rotate --2 Left Rotation
        end
        print()
        print()
    else
        player.rotation_orientation = 0
        player.rotating = 0
        player.moving = 1
        return 0, 0
    end
end

function decision()
    if(not player.inited) then
        --print(0)
        return 0
    end
    --print()
    --print(player.moving)
    --print(player.rotating)
    --print()

    if enemy.health == 0 or
            (player.moving == 0 and player.killing == 0 and player.rotating == 0) then
        resetPlayer()
        --print(1)
        return 1
    end
    if player.killing == 1 then
        --print(2)
        return 2
    end
    if player.moving == 1 then
        --print(3)
        return 3
    end
    if player.rotating == 1 then
        --print(4)
        return 4
    end
    --print(0)
    return 0
end
