from fastapi import APIRouter, HTTPException, Depends
from sqlalchemy.orm import Session
from routers.schemas import MemoCreate, MemoUpdate, MemoResponse
from database import get_db
from models import Memo

router = APIRouter(tags=["WEEK2"])

@router.get("/", response_model=list[MemoResponse])
def get_memos(db: Session = Depends(get_db)):
    return db.query(Memo).all()

@router.post("/", status_code=201, response_model=MemoResponse)
def create_memo(memo: MemoCreate, db: Session = Depends(get_db)):
    new_memo = Memo(title=memo.title, body=memo.body)
    db.add(new_memo)
    db.commit()
    db.refresh(new_memo)
    return new_memo

@router.get("/{memo_id}", response_model=MemoResponse)
def read_memo(memo_id: int, db: Session = Depends(get_db)):
    memo = db.query(Memo).filter(Memo.id == memo_id).first()
    if not memo:
        raise HTTPException(status_code=404, detail="메모를 찾을 수 없습니다.")
    return memo

@router.put("/{memo_id}", response_model=MemoResponse)
def update_memo(memo_id: int, memo: MemoUpdate, db: Session = Depends(get_db)):
    existing = db.query(Memo).filter(Memo.id == memo_id).first()
    if not existing:
        raise HTTPException(status_code=404, detail="메모를 찾을 수 없습니다.")
    
    update_data = memo.model_dump(exclude_unset=True)
    for key, value in update_data.items():
        setattr(existing, key, value)

    db.commit()
    db.refresh(existing)
    return existing

@router.delete("/{memo_id}", status_code=204)
def delete_memo(memo_id: int, db: Session = Depends(get_db)):
    memo = db.query(Memo).filter(Memo.id == memo_id).first()
    if not memo:
        raise HTTPException(status_code=404, detail="메모를 찾을 수 없습니다.")
    db.delete(memo)
    db.commit()
