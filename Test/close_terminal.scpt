tell application "iTerm"
    # Tüm pencereleri kapat
    set allWindows to every window
    repeat with aWindow in allWindows
        close aWindow
    end repeat
end tell

