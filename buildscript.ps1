param(
    [switch]$Debug
)

$config = if ($Debug) { "Debug" } else { "Release" }

$jsonContent = Get-Content -Raw -Path "info.json" | ConvertFrom-Json
$name = $jsonContent.name

$zipFile = "$name.zip"
$scriptFile = "$name.script"

if (Test-Path $zipFile) {
    Remove-Item $zipFile -Force
}
if (Test-Path $scriptFile) {
    Remove-Item $scriptFile -Force
}

Compress-Archive -Path "info.json" -DestinationPath $zipFile

cmake -S . -B build
cmake --build ./build --config $config

$buildDir = "build/$config"
$dllFiles = Get-ChildItem -Path $buildDir -Filter "*.dll"
foreach ($dll in $dllFiles) {
    Compress-Archive -Update -Path $dll.FullName -DestinationPath $zipFile
}

Rename-Item -Path $zipFile -NewName $scriptFile -Force

Write-Output "Created $scriptFile using $config."
