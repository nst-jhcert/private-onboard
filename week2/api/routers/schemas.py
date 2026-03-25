from pydantic import BaseModel, Field
from datetime import datetime

class MemoCreate(BaseModel):
    title: str = Field(..., min_length=1, examples=["회의록"])
    body: str | None = Field(None, examples=["출근을 하기로 결정하였습니다."])

class MemoUpdate(BaseModel):
    title: str | None = Field(None, min_length=1, examples=["회의록"])
    body: str | None = Field(None, examples=["퇴근을 하기로 결정하였습니다."])

class MemoResponse(BaseModel):
    id: int
    title: str
    body: str | None
    created_at: datetime
    updated_at: datetime