local Translations = {
    ["Dead Rails"] = "死亡铁轨",
    ["Main"] = "主菜单",
    ["Misc"] = "杂项",
    ["UI Settings"] = "界面设置",
    ["Credit / Join"] = "鸣谢/加入",
    ["Search"] = "搜索",
    ["Distance [ Nah ]"] = "距离 [ 无 ]",
    ["Time [ 6:00 AM ]"] = "时间 [ 早上6点 ]",
    ["Return Check"] = "返回检查",
    ["Teleport To Train"] = "传送至火车",
    ["Teleport To Castle"] = "传送至城堡",
    ["Teleport To TeslaLab"] = "传送至特斯拉实验室",
    ["Teleport To End"] = "传送至终点",
    ["Esp"] = "显示ESP",
    ["Esp Train"] = "显示火车ESP",
    ["Esp Ore"] = "显示矿石ESP",
    ["Esp Player"] = "显示玩家ESP",
    ["Item Esp"] = "显示物品ESP",
    ["Esp Item"] = "显示物品ESP",
    ["Esp Money"] = "显示金钱ESP",
    ["No Cooldown Proximity"] = "无冷却接近",
    ["Unlock Person"] = "解锁角色",
    ["Auto Fuel Train"] = "自动给火车加油",
    ["Weld Item"] = "焊接物品",
    ["Auto Sell"] = "自动出售",
    ["Choose Store"] = "选择商店",
    ["Auto Store Item"] = "自动存储物品",
    ["Complete Assembly Tesla"] = "完成特斯拉组装",
    ["Esp Fuel"] = "显示燃料ESP",
    ["Esp Mods"] = "显示模组ESP",
    ["Esp Bank / Code"] = "显示银行/代码ESP",
    ["Esp High Light"] = "高亮ESP",
    ["Esp Gui"] = "显示界面ESP",
    ["Text Size [ Gui ]"] = "界面文字大小",
    ["Esp Name"] = "显示名字ESP",
    ["Esp Distance"] = "显示距离ESP",
    ["Esp Health"] = "显示生命值ESP",
    ["Combat"] = "战斗",
    ["Full Bright"] = "全亮度",
    ["No Fog"] = "无雾",
    ["Noclip"] = "穿墙",
    ["Choose Collect"] = "选择收集",
    ["Auto Collect"] = "自动收集",
    ["Auto Banjo Heal"] = "自动班卓琴治疗",
    ["Notification Unicorn"] = "独角兽通知",
    ["Spawn Notification"] = "生成通知",
    ["Notification Spawn"] = "通知生成",
    ["WalkSpeed"] = "移动速度",
    ["Show Health Bar Mods"] = "显示模组血条",
    ["Character Mods"] = "角色模组",
    ["No Mods"] = "无模组",
    ["Attack Melee"] = "近战攻击",
    ["Auto Attack Melee"] = "自动近战攻击",
    ["Head"] = "头部",
    ["HumanoidRootPart"] = "人形根部件",
    ["Money"] = "金钱",
    ["Snake Oil"] = "蛇油",
    ["Bandage"] = "绷带",
    ["Bond"] = "债券",
    ["Ammo"] = "弹药",
    ["Holy Water"] = "圣水",
    ["Gun"] = "枪",
    ["Molotov"] = "燃烧瓶",
    ["Melee"] = "近战武器",
    ["Sterling"] = "斯特林",
    ["Stillwater Prison"] = "静水监狱",
    ["Fort Constitution"] = "宪法要塞",
    ["Horse"] = "马匹",
    ["Wolf"] = "狼",
    ["Werewolf"] = "狼人",
    ["Gun Aura"] = "枪支光环",
    ["Charge"] = "冲锋",
    ["Attack Fast"] = "快速攻击",
    ["Ustal Kill Lag"] = "延迟击杀",
    ["Ustal Kill No Lag"] = "无延迟击杀",
    ["Delay Shot"] = "延迟射击",
    ["Reach Shot"] = "远程射击",
    ["Auto Reload Gun"] = "自动换弹",
    ["Hitbox Mods"] = "碰撞箱模组",
    ["Eat Mods"] = "进食模组",
    ["Aimbot Mods"] = "自瞄模组",
    ["Camlock Mods"] = "锁视角模组",
    ["Health Heal"] = "生命治疗",
    ["Auto Heal"] = "自动治疗"
}

local function translateText(text)
    if not text or type(text) ~= "string" then return text end
    if Translations[text] then return Translations[text] end
    for en, cn in pairs(Translations) do
        if text:find(en) then return text:gsub(en, cn) end
    end
    return text
end

local function setupTranslationEngine()
    local success, err = pcall(function()
        local oldIndex = getrawmetatable(game).__newindex
        setreadonly(getrawmetatable(game), false)
        getrawmetatable(game).__newindex = newcclosure(function(t, k, v)
            if (t:IsA("TextLabel") or t:IsA("TextButton") or t:IsA("TextBox")) and k == "Text" then
                v = translateText(tostring(v))
            end
            return oldIndex(t, k, v)
        end)
        setreadonly(getrawmetatable(game), true)
    end)
    if not success then
        warn("元表劫持失败:", err)
        local translated = {}
        local function scanAndTranslate()
            for _, gui in ipairs(game:GetService("CoreGui"):GetDescendants()) do
                if (gui:IsA("TextLabel") or gui:IsA("TextButton") or gui:IsA("TextBox")) and not translated[gui] then
                    pcall(function()
                        local text = gui.Text
                        if text and text ~= "" then
                            local translatedText = translateText(text)
                            if translatedText ~= text then
                                gui.Text = translatedText
                                translated[gui] = true
                            end
                        end
                    end)
                end
            end
            local player = game:GetService("Players").LocalPlayer
            if player and player:FindFirstChild("PlayerGui") then
                for _, gui in ipairs(player.PlayerGui:GetDescendants()) do
                    if (gui:IsA("TextLabel") or gui:IsA("TextButton") or gui:IsA("TextBox")) and not translated[gui] then
                        pcall(function()
                            local text = gui.Text
                            if text and text ~= "" then
                                local translatedText = translateText(text)
                                if translatedText ~= text then
                                    gui.Text = translatedText
                                    translated[gui] = true
                                end
                            end
                        end)
                    end
                end
            end
        end
        local function setupDescendantListener(parent)
            parent.DescendantAdded:Connect(function(descendant)
                if descendant:IsA("TextLabel") or descendant:IsA("TextButton") or descendant:IsA("TextBox") then
                    task.wait(0.1)
                    pcall(function()
                        local text = descendant.Text
                        if text and text ~= "" then
                            local translatedText = translateText(text)
                            if translatedText ~= text then
                                descendant.Text = translatedText
                            end
                        end
                    end)
                end
            end)
        end
        pcall(setupDescendantListener, game:GetService("CoreGui"))
        local player = game:GetService("Players").LocalPlayer
        if player and player:FindFirstChild("PlayerGui") then
            pcall(setupDescendantListener, player.PlayerGui)
        end
        while true do
            scanAndTranslate()
            task.wait(3)
        end
    end
end

task.wait(2)
setupTranslationEngine()

local success, err = pcall(function()
    loadstring(game:HttpGet("https://raw.githubusercontent.com/Articles-Hub/ROBLOXScript/refs/heads/main/File-Script/Dead%20rails.lua"))()
end)

if not success then
    warn("加载失败:", err)
end
