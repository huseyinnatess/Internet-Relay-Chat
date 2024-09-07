tell application "iTerm"
    # İlk pencereyi aç (server) ve sağ altta konumlandır
    set newWindow to (create window with default profile)
    tell current session of newWindow
        write text "cd /Users/huates/Desktop/Ft_irc && make && ./ircserv"
    end tell
    -- İlk pencereyi sağ altta konumlandır
    tell newWindow
        set bounds of newWindow to {1400, 600, 2100, 1000} -- Daha sağda sağ alt kısmı
    end tell

    -- Bekleme süresi
    delay 1.5 -- Sunucunun başlatılması için yarım saniye bekleyin

    # İkinci pencereyi aç (nc) ve sağ üstte konumlandır
    -- set newWindow2 to (create window with default profile)
    -- tell current session of newWindow2
    --    write text "nc localhost 8888"
    -- end tell
    -- İkinci pencereyi sağ üstte konumlandır
    -- tell newWindow2
       -- set bounds of newWindow2 to {1400, 100, 2100, 500} -- Daha sağda sağ üst kısmı
    -- end tell
end tell

