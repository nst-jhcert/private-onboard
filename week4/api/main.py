"""Week4 API server for CSP/CCSDS packet handling."""

from fastapi import FastAPI

api = FastAPI(
    title="ONBOARD-WEEK4",
    docs_url="/docs",
    redoc_url="/redoc",
)


@api.get("/")
def root():
    """Health check endpoint."""
    return {"status": "OK"}
