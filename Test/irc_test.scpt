tell application "iTerm"
    # İlk pencereyi aç (server) ve sağ altta konumlandır
    set newWindow to (create window with default profile)
    tell current session of newWindow
        write text "cd /Users/huates/Desktop/Ft_irc && make && ./ircserv"
    end tell
    -- İlk pencereyi sağ altta konumlandır
    tell newWindow
        set bounds of newWindow to {1400, 600, 2100, 1000} -- Sağ altta
    end tell

    -- Bekleme süresi
    delay 1.5 -- Sunucunun başlatılması için bekleyin

    # İkinci pencereyi aç (nc) ve sağ üstte konumlandır
    set newWindow2 to (create window with default profile)
    tell current session of newWindow2
        write text "nc localhost 8888"
    end tell
    -- İkinci pencereyi sağ üstte konumlandır
    tell newWindow2
        set bounds of newWindow2 to {1400, 100, 2100, 500} -- Sağ üstte
    end tell

    -- Bekleme süresi
    delay 0.5

    # Üçüncü pencereyi aç (nc) ve sağ orta konumlandır
    set newWindow3 to (create window with default profile)
    tell current session of newWindow3
        write text "nc localhost 8888"
    end tell
    -- Üçüncü pencereyi sağ orta konumlandır
    tell newWindow3
        set bounds of newWindow3 to {1400, 510, 2100, 590} -- Sağ üst ile sağ alt arasında
    end tell
end tell
