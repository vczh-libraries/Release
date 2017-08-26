pushd %~dp0
rmdir /S /Q FullControlTest
robocopy ..\..\..\..\..\GacUI\Test\GacUISrc\Host\Resources\FullControlTest FullControlTest /E
mkdir FullControlTest\Source
call ..\..\..\..\Tools\GacGen FullControlTest\Resource.xml
popd