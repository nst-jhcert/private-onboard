from fastapi import FastAPI
from routers import memos

api = FastAPI(
    title="ONBOARD-WEEK2",
    description="""
## ONBOARD-WEEK2
### 목표
- 컨테이너로 분리된 메모 앱을 구현합니다.
### 기술스택
- FastAPI
- Docker
- PostgreSQL
- Redis
""", 
    version="1.0.0",
    docs_url="/docs",
    redoc_url="/redoc",
)

api.include_router(memos.router, prefix="/memos", tags=["WEEK2"])

@api.get("/", summary="서버의 상태를 반환합니다.", tags=["WEEK2"])
async def root():
    return "OK"