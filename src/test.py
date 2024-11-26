import requests

url = "https://api.taapi.io/bulk"

payload = {
    "secret": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJjbHVlIjoiNjVlMjRhYjkyYzczYzFlM2ZkYTU5M2YyIiwiaWF0IjoxNzMyMjc2ODQxLCJleHAiOjMzMjM2NzQwODQxfQ.G_YJFM2P7T_SAsDtGCA9_UmoxnjrHYAtJqzCwt6wYNA",
    "construct": {
        "exchange": "binance",
        "symbol": "XRP/USDT",
        "interval": "5m",
        "indicators": [
            {
                "indicator": "rsi"
            },
            {
                "indicator": "ema",
                "period": 20,
            },
            {
                "indicator": "ema",
                "period": 50,
            },
            {
                "indicator": "ema",
                "period": 200,
            },
            {
                "indicator": "macd"
            }, 
            {
                "indicator": "kdj"
            },
            {
                "indicator": "atr"
            }
        ]
    }
}
headers = {"Content-Type": "application/json"}

response = requests.post(url, json=payload, headers=headers)
data = response.json()

for item in data["data"]:
    indicator = item["indicator"]
    result = item["result"]
    
    if isinstance(result, dict):
        print(f"{indicator}:")
        for key, value in result.items():
            print(f"  {key}: {value}")
    else:
        print(f"{indicator}: {result}")