
void handleWebPage(){
  String html = R"rawliteral(
      <!DOCTYPE html>
      <html>
      <head>
          <meta charset="UTF-8">
          <meta name="viewport" content="width=device-width, initial-scale=1.0">  <!-- 使網頁在手機上適應螢幕寬度 -->
          <title>WiFi Manager</title>
          <style>
              /* 隱藏所有預設按鈕 */
              #save, #cancel, #back {
                  display: none;
              }
              
              /* 自訂按鈕樣式 */
              .custom-button {
                  background-color: #4CAF50;
                  color: white;
                  padding: 12px 24px;  /* 修改為適合手機的按鈕大小 */
                  text-align: center;
                  text-decoration: none;
                  display: inline-block;
                  font-size: 16px;
                  margin: 10px 2px;
                  cursor: pointer;
                  width: 100%;  /* 讓按鈕寬度填滿手機螢幕 */
                  box-sizing: border-box;
              }

              /* 設定表單元素的樣式 */
              label, input {
                  display: block;
                  width: 100%;
                  margin-bottom: 12px;  /* 增加間距 */
                  font-size: 16px;
              }

              input[type="text"] {
                  padding: 8px;
                  font-size: 16px;
                  border: 1px solid #ccc;
                  border-radius: 4px;
              }

              /* 頁面容器樣式 */
              body {
                  font-family: Arial, sans-serif;
                  margin: 0;
                  padding: 20px;
                  background-color: #f4f4f4;
                  color: #333;
              }

              h1 {
                  text-align: center;
                  font-size: 24px;
                  color: #333;
              }

              /* 響應式設計：在手機螢幕上自動調整頁面 */
              @media (max-width: 600px) {
                  h1 {
                      font-size: 20px;  /* 當螢幕寬度小於600px時，縮小標題字型 */
                  }

                  .custom-button {
                      font-size: 18px;  /* 調整按鈕字型大小 */
                      padding: 14px 30px;  /* 按鈕內邊距調整為適合小螢幕 */
                  }

                  label, input {
                      font-size: 14px;  /* 減小標籤和輸入框的字型 */
                  }
              }

              /* 代辦事項樣式 */
              .todo-item {
                  display: flex;
                  justify-content: space-between;
                  margin-bottom: 10px;
              }
          
              /* 放大並加粗代辦事項標籤 */
              .todo-label {
                  font-size: 26px;
                  font-weight: bold;
              }

              /* 讓勾選框和文案在同一行顯示 */
              .inline {
                  display: flex;
                  justify-content: space-between;
                  margin-left:auto;
              }
          </style>
      </head>
      <body>
          <h1>E-Paper 萬年曆資料輸入</h1>
          <form method="POST" action="/save" id="main-form">
              <div class="inline">
                  <div ><input type="checkbox" id="modify-date" name="modify-date"></div>
                  <label for="modify-date">是否修改日期?</label>
              </div>

              <div id="date-inputs" style="display: none;">
                  <label for="Year">年(ex:2025):</label>
                  <input type="number" id="Year" name="Year" value="@Year@"><br>

                  <label for="Moon">月(ex:2):</label>
                  <input type="number" id="Moon" name="Moon" value="@Moon@"><br><br>

                  <label for="Day">日(ex:1):</label>
                  <input type="number" id="Day" name="Day" value="@Day@"><br><br>

                  <label for="Time">時間:24小時制(EX:13:00)</label>
                  <input type="time" id="Time" name="Time" value="@Time@" step="60"><br><br>
              </div>
          
              <label for="Offset">輸入補償（負數為每天要減少幾秒）單位是秒:</label>
              <input type="text" id="Offset" pattern="-?\d*" name="Offset" value="@Offset@"><br><br>

              <label for="DelayTime">幾秒更新1次:</label>
              <input type="number" id="DelayTime" name="DelayTime" value="@DelayTime@"><br><br>

              <label for="todo-list" class="todo-label">代辦事項列表</label>
              <div id="todo-list"></div>
              
              <!-- 自訂按鈕 -->
              <button type="submit" class="custom-button">儲存設定</button>
              <input type="hidden" id="todos" name="todos" value="@todo-list@">
          </form>

          <h1>新增代辦事項</h1>
          <form id="todo-form">
              <input type="date" id="todo-date" required>
              <input type="text" id="todo-name" maxlength="10" placeholder="事件名稱" required>
              <button type="submit" class="custom-button">新增代辦事項</button>
          </form>
          

          <script>
              const todoItems = [];

              document.getElementById('modify-date').addEventListener('change', function() {
                  const dateInputs = document.getElementById('date-inputs');
                  if (this.checked) {
                      dateInputs.style.display = 'block';
                  } else {
                      dateInputs.style.display = 'none';
                  }
              });

              document.getElementById('todo-form').addEventListener('submit', function(event) {
                  event.preventDefault();
                  if (todoItems.length >= 20) {
                      alert('最多只能新增20筆代辦事項');
                      return;
                  }

                  const date = document.getElementById('todo-date').value;
                  const name = document.getElementById('todo-name').value;

                  if (date && name) {
                      const todoList = document.getElementById('todo-list');
                      const todoItem = document.createElement('div');
                      todoItem.className = 'todo-item';
                      todoItem.innerHTML = `
                          <span>${date} - ${name}</span>
                          <button onclick="removeTodoItem(this, '${date}', '${name}')">刪除</button>
                      `;
                      todoList.appendChild(todoItem);

                      // 清空輸入欄位
                      document.getElementById('todo-date').value = '';
                      document.getElementById('todo-name').value = '';

                      // 將代辦事項資料新增到陣列中
                      todoItems.push({ date, name });

                      // 對 todoItems 陣列按日期進行排序（由舊到新）
                      todoItems.sort((a, b) => {
                          return new Date(a.date) - new Date(b.date);
                      });

                      // 更新隱藏的輸入欄位
                      updateHiddenTodos();
                  }
              });

              function removeTodoItem(button, date, name) {
                  // 移除代辦事項元素
                  button.parentElement.remove();

                  // 從陣列中移除代辦事項
                  const index = todoItems.findIndex(item => item.date === date && item.name === name);
                  if (index !== -1) {
                      todoItems.splice(index, 1);
                  }

                  // 更新隱藏的輸入欄位
                  updateHiddenTodos();
              }

              function updateHiddenTodos() {
                  const mainForm = document.getElementById('main-form');
                  let hiddenTodos = document.querySelector('input[name="todos"]');
                  if (!hiddenTodos) {
                      hiddenTodos = document.createElement('input');
                      hiddenTodos.type = 'hidden';
                      hiddenTodos.name = 'todos';
                      mainForm.appendChild(hiddenTodos);
                  }
                  hiddenTodos.value = JSON.stringify(todoItems);
              }

              function loadTodosFromHiddenField() {
                  const hiddenTodos = document.querySelector('input[name="todos"]');
                  if (hiddenTodos) {
                      const todos = JSON.parse(hiddenTodos.value);
                      todos.forEach(todo => {
                          const todoList = document.getElementById('todo-list');
                          const todoItem = document.createElement('div');
                          todoItem.className = 'todo-item';
                          todoItem.innerHTML = `
                              <span>${todo.date} - ${todo.name}</span>
                              <button onclick="removeTodoItem(this, '${todo.date}', '${todo.name}')">刪除</button>
                          `;
                          todoList.appendChild(todoItem);

                          // 將代辦事項資料新增到陣列中
                          todoItems.push(todo);
                      });

                      // 按照日期排序
                      todoItems.sort((a, b) => {
                          return new Date(a.date) - new Date(b.date);
                      });
                  }
              }

              // 當頁面載入時，更新 UI
              window.onload = loadTodosFromHiddenField;
          </script>
      </body>
      </html>
    )rawliteral";
  if(prefs.getInt("BL8025T",0) == 1 ){
    tm timeinfo = getRTCTime() ;
    html.replace("@Year@",String(timeinfo.tm_year));
    html.replace("@Moon@",String(timeinfo.tm_mon));
    html.replace("@Day@",String(timeinfo.tm_mday));
    html.replace("@Time@",String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min));
  }else{
    html.replace("@Year@",prefs.getString("year"));
    html.replace("@Moon@",prefs.getString("month"));
    html.replace("@Day@",prefs.getString("day"));
    html.replace("@Time@",prefs.getString("time"));
  }
  html.replace("@Offset@",prefs.getString("offset","0"));
  html.replace("@DelayTime@", String(prefs.getInt("delayTime",30)));

  String todoList = prefs.getString("todos");
  todoList.replace("\"", "&quot;");  // 先修改字串  
  html.replace("@todo-list@",todoList);

  wifiManager.server->send(200, "text/html", html);
}


void handleSaveWebPage(){
  Serial.println("handleSaveWebPage");
  String check  =  wifiManager.server->arg("modify-date");
  //Serial.println(year.c_str());
  if ( check == "on" ) {
    prefs.putString("year",wifiManager.server->arg("Year"));
    prefs.putString("month",wifiManager.server->arg("Moon"));
    prefs.putString("day",wifiManager.server->arg("Day"));
    prefs.putString("time",wifiManager.server->arg("Time"));
    prefs.putInt("set",1);

    //更新時間
    String str = wifiManager.server->arg("Time");
    int commaIndex = str.indexOf(':');
    String hour = str.substring(0, commaIndex);
    String min = str.substring(commaIndex + 1);
    setRTC(wifiManager.server->arg("Year").toInt(),wifiManager.server->arg("Moon").toInt(),wifiManager.server->arg("Day").toInt(), hour.toInt() , min.toInt(), 0) ;
  }
  
  prefs.putString("offset",wifiManager.server->arg("Offset"));
  prefs.putInt("delayTime",wifiManager.server->arg("DelayTime").toInt());
  if(prefs.getInt("delayTime",0) != 0){
    delayTime = prefs.getInt("delayTime",0);
  }

  String todoList = wifiManager.server->arg("todos");  
  prefs.putString("todos",todoList);
  prefs.end();
  prefs.begin("Calendar");
  
  /*if(prefs.getInt("BL8025T",0) == 1 ){
    Wire.begin(I2C_SDA, I2C_SCL);  
    int offset = atoi(prefs.getString("offset","0").c_str());
    setCalibration(offset);
    displayCalibration();
    Wire.end();  // 關閉 I2C，降低功耗
  }*/
  String html = R"rawliteral(
        <!DOCTYPE html>
        <html>
        <head>
          <meta charset="UTF-8">
        </head>
        <body>
            <h1>E-Paper 萬年曆資料設定完成</h1>
            <p>請等待5秒鐘後自動重啟，或是按第一個按鈕可以手動重啟</p>
        </body>
        </html>
    )rawliteral";
  wifiManager.server->send(200, "text/html", html);

  mode = 2;
  //主畫面模式  
  showMainModePage();
  wifiManager.stopConfigPortal(); 
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);//關閉WIFI功能
  //delay(2000);

  //ESP.restart();

}
void customWebPage() {
  Serial.println("customWebPage");
  wifiManager.server->on("/", handleWebPage);  
  wifiManager.server->on("/save", handleSaveWebPage);  
}


void setCalibration(int value) {
  uint8_t calReg = 0;
  
  // 準備校準值寄存器
  if (value >= 0) {
    calReg = (uint8_t)value & 0x3F;  // 正值: 低6位
  } else {
    calReg = ((uint8_t)(-value) & 0x3F) | 0x80;  // 負值: 低6位 + 符號位
  }
  
  writeRegister(REG_CTRL1, 0x00); // 啟用24小時模式
  // Dafault value of temperature compensation interval is 2 seconds
  writeRegister(REG_CTRL2, 0x00); 
  delay(2000);
  writeRegister(REG_RTC_EXT, 0x00); 

  writeRegister(REG_CAL, calReg);
}


// 寫入寄存器
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(BL8025T_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// 顯示當前校準值
void displayCalibration() {
  uint8_t calReg = readRegister(REG_CAL);
  int calValue;
  
  // 解釋校準值
  if (calReg & 0x80) {
    // 負值
    calValue = -((int)(calReg & 0x3F));
  } else {
    // 正值
    calValue = calReg & 0x3F;
  }
  
  Serial.println("當前校準值: " + String(calValue));
  Serial.println("當前REG_CTRL1: " + String(readRegister(REG_CTRL1)));
  Serial.println("當前REG_CTRL2: " + String(readRegister(REG_CTRL2)));
  Serial.println("當前REG_RTC_EXT: " + String(readRegister(REG_RTC_EXT)));
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(BL8025T_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(BL8025T_ADDR, 1);
  return Wire.read();
}



void showAPModePage(){
  
  //WiFi.setSleep(false);
  display.setPartialWindow(200, 100, 500, 200 );
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();

  do {  
    //textCh34("請連線熱點AutoConnectAP", 235, 160, GxEPD_BLACK, GxEPD_WHITE);  
    textCh("請連線熱點AutoConnectAP", 235, 190, GxEPD_BLACK, GxEPD_WHITE); 
    textCh("在網址列上輸入192.168.4.1進行編輯", 235, 230, GxEPD_BLACK, GxEPD_WHITE); 

  } while (display.nextPageBW());
  display.powerOff();


  wifiManager.setWebServerCallback(customWebPage);
  wifiManager.startConfigPortal("AutoConnectAP");
}

