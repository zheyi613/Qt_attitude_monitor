# Qt_attitude_monitor
Use Qt GUI to visualize attitude and plot 6-axis data

## GUI

![image](https://user-images.githubusercontent.com/86707047/192147313-6e02f8c6-44e5-431f-af74-5dc4ea2f298d.png)

## 使用步驟

1. 下載 `release.zip`，解壓縮後開啟資料夾內 `monitor.exe`，不需安裝 Qt
2. 選擇 `串列埠 (Serial port)`、`鮑率 (Baudrate)`
3. 輸入 `資料封包速率 (Packet rate)`
4. 點擊 `Connect` 按鈕，此時按鈕會變成 `Disconnected`， 即可開始透過串列埠接收六軸資料進行繪圖
5. 若要斷開連線，則點擊 `Disconnected`，停止接收時可使用滑鼠對圖表進行 `拖曳`、`滾輪放大`

### Note
- 每個封包中以逗號 (',') 隔開，最後為換行符號 ('\n') ，不需回車 ('\r')
- format : "accel_x,accel_y,accel_z,roll,pitch,yaw\n"
- 時間軸由封包速率 (感測器主控端) 決定，非計時器計算
- 立方體與圖表更新率為 60fps
