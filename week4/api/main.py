"""Week4 API server for CSP/CCSDS packet handling."""

from fastapi import FastAPI

from routers import csp

api = FastAPI(
    title="ONBOARD-WEEK4",
    docs_url="/docs",
    redoc_url="/redoc",
)

api.include_router(csp.router, prefix="/csp", tags=["CSP"])


@api.get("/")
def root():
    """Health check endpoint."""
    return {"status": "OK"}
