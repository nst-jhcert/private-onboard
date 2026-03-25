from fastapi import APIRouter, HTTPException
from routers.schemas import MemoCreate, MemoUpdate, MemoResponse

router = APIRouter(tags=["WEEK2"])

@router.get("/", response_model=list[MemoResponse])
async def get_memos():
    return 0

@router.post("/", status_code=201, response_model=list[MemoResponse])
async def create_memo(memo: MemoCreate):
    return 0

@router.get("/{memo_id}", response_model=list[MemoResponse])
async def read_memo(memo_id: int):
    return 0

@router.put("/{memo_id}", status_code=201, response_model=list[MemoResponse])
async def update_memo(memo_id: int, memo: MemoUpdate):
    return 0

@router.delete("/{memo_id}", status_code=204)
async def delete_memo(memo_id: int):
    pass