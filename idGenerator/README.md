# Distributed Unique ID Generator

This project is to demonstrate the distributed unique ID generator solution. 

## Running the example

### Environment setup

```
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### Running the Example

In the first terminal:

```
cd idGenerator/
source venv/bin/activate
export MACHINE_ID=1
uvicorn main:app --reload --port 8000
```

In the second terminal:

```
cd idGenerator/
source venv/bin/activate
export MACHINE_ID=2
uvicorn main:app --reload --port 8001
```

In the third terminal:

```
cd idGenerator/
source venv/bin/activate
export MACHINE_ID=3
uvicorn main:app --reload --port 8002
```

In the final terminal:

```
cd idGenerator/
source venv/bin/activate
python client.py
```