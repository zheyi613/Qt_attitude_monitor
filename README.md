# Qt_attitude_monitor
Use Qt GUI to visualize attitude and plot 9-axis data

## GUI

![image](https://user-images.githubusercontent.com/86707047/235585595-66f254bb-3553-4211-8283-6ee7abcb648b.png)

## 使用步驟

1. 在 `release` 下載 `AttitudeMonitor_vx.x.x.zip`，解壓縮後開啟資料夾內 `monitor.exe`，不需安裝 Qt
2. 選擇 `串列埠 (Serial port)`、`鮑率 (Baudrate)`
3. 輸入 `資料封包速率 (Packet rate)`
4. 選擇 `座標系(Coordinate)`
5. 點擊 `Connect` 按鈕，此時按鈕會變成 `Disconnected`， 即可開始透過串列埠接收六軸資料進行繪圖
6. 若要斷開連線，則點擊 `Disconnected`，停止接收時可使用滑鼠對圖表進行 `拖曳`、`滾輪放大`

### Note
- 串列埠參數 : `8 bits`、`No parity`、`One stop bit`、`No flow control`
- 每個封包中以逗號 `','` 隔開，最後為換行符號 `'\n'` ，不需回車 `'\r'`
- format : `"accel_x,accel_y,accel_z,gyro_x,gyro_y,gyro_z,roll,pitch,yaw\n"`
- 時間軸由封包速率 (感測器主控端) 決定，非計時器計算
- NED :
  - roll (X-axis, North) : 射出螢幕
  - pitch (Y-axis, East) : 左方
  - yaw (Z-axis, Down) : 下方
- ENU :
  - roll (Y-axis, North) : 射出螢幕
  - pitch (X-axis, East) : 左方
  - yaw (Z-axis, Up) : 上方
- 立方體與圖表更新率為 60 FPS
- 若串列埠出現錯誤 ex : 存取遭拒，會跳出通知，並提示原因，串列埠回復成未連接狀態，如步驟 4.，可點擊 `Connect` 嘗試重新連接
